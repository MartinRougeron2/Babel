/*
** EPITECH PROJECT, 2021
** B-CPP-500-LYN-5-1-babel-martin.rougeron
** File description:
** Asqlite3
*/

#include "client/Asqlite3.hpp"
#include "iostream"

Asqlite3::Asqlite3()
{
	std::string sql = "CREATE TABLE IF NOT EXISTS user("
		"id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"pseudo TEXT NOT NULL UNIQUE, "
		"password TEXT NOT NULL, "
		"address	TEXT NOT NULL);"
		"CREATE TABLE IF NOT EXISTS contact("
		"idfrom INTEGER, "
		"idto INTEGER, "
		"FOREIGN KEY(idfrom) REFERENCES user(id), "
		"FOREIGN KEY(idto) REFERENCES user(id));";
	if (!executeQuery(sql, NULL, 0))
		std::cerr << "Error in createTable function." << std::endl;
}

Asqlite3::~Asqlite3()
{
}

bool Asqlite3::uploadData(struct User user)
{
	std::string sql("INSERT INTO user (pseudo, password, address)"
	"VALUES('" + user.username + "', '" + user.password + "', '" + user.address + "');");
	if (!executeQuery(sql, NULL, 0)) {
		std::cerr << "Error in upload new user" << std::endl;
		return false;
	}
	return true;
}

int Asqlite3::callbackUserExist(void *context, int argc, char** argv, char** azColName)
{
	Asqlite3 *db = static_cast<Asqlite3 *>(context);
	for (int i = 0; i < argc; i++) {
		db->_res = argv[i];
	}
	return 0;
}

int Asqlite3::callbackGetUser(void *context, int argc, char** argv, char** azColName)
{
	Asqlite3 *db = static_cast<Asqlite3 *>(context);
	for (int i = 0; i < argc; i++) {
		db->_res += argv[i];
		db->_res += "\n";
	}
	return 0;
}

Asqlite3::loginCode Asqlite3::login(struct User user)
{
	std::string sql = SELECT_QUERY("pseudo") +
	FROM_QUERY("user") +
	WHERE_QUERY("pseudo = '" + user.username + "';");
	this->_res.clear();
	if (!executeQuery(sql, callbackUserExist, this))
		std::cerr << "Error in login function.1" << std::endl;
	if (user.username != this->_res)
		return USER_NOT_EXIST;
	this->_res.clear();
	sql = SELECT_QUERY("pseudo") +
	FROM_QUERY("user") +
	WHERE_QUERY("pseudo = '" + user.username + "' AND pseudo = '" + user.username + "';");
	if (!executeQuery(sql, callbackUserExist, this))
		std::cerr << "Error in login function.2" << std::endl;
	if (user.username != this->_res)
		return BAD_PASSWORD;
	this->_res.clear();
	return SUCCESS;
}

std::string Asqlite3::getUser(std::string name)
{
	std::string sql = SELECT_QUERY("pseudo") +
	FROM_QUERY("user") +
	WHERE_QUERY("pseudo LIKE '" + name + "%';");
	this->_res.clear();
	if (!executeQuery(sql, callbackGetUser, this)) {
		std::cerr << "Error in getUser function." << std::endl;
	}
	return this->_res;
}

bool Asqlite3::linkUser(std::string from, std::string to)
{
	std::string idfrom = getIdByUsername(from);
	std::string idto = getIdByUsername(to);
	if (idfrom.empty() || idto.empty()) {
		std::cerr << "Not valid user" << std::endl;
		return false;
	}
	this->getLinkedUser(from);
	for (auto user : this->_linkedUser)
		if (from != user.username)
			return false;
	std::string sql = "INSERT INTO contact(idfrom, idto) VALUES(" + idfrom + ", " + idto + ");";
	if (!executeQuery(sql, NULL, 0)) {
		std::cerr << "Error in linkUser function." << std::endl;
		return false;
	}
	return true;
}

std::string Asqlite3::getIdByUsername(std::string username)
{
	std::string sql = SELECT_QUERY("id") +
		FROM_QUERY("user") +
		WHERE_QUERY("pseudo = '" + username + "';");
	this->_res.clear();
	if (!executeQuery(sql, callbackUserExist, this))
		std::cerr << "Error in getid function." << std::endl;
	if (this->_res.empty())
		return "";
	return (this->_res);
}

int Asqlite3::callbackFillContact(void *context, int argc, char** argv, char** azColName)
{
	Asqlite3 *db = static_cast<Asqlite3 *>(context);
	std::string username, address;

	for (int i = 0; i < argc; i = i + 2) {
		db->_linkedUser.push_back({std::string(argv[i]), std::string(""), std::string(argv[i + 1])});
	}
	return 0;
}

std::vector<struct User> Asqlite3::getLinkedUser(std::string username)
{
	std::string id = getIdByUsername(username);
	std::string sql = SELECT_QUERY("pseudo, address") +
		FROM_QUERY("contact") +
		INNERJOIN_QUERY("user ON user.id=contact.idfrom OR user.id=contact.idto ") +
		WHERE_QUERY("user.id != "+id+" AND (contact.idfrom = "+id+" OR contact.idto = "+id+")");
	this->_linkedUser.clear();
	if (!executeQuery(sql, callbackFillContact, this))
		std::cerr << "Error in getid function." << std::endl;
	return this->_linkedUser;
}

bool Asqlite3::executeQuery(std::string sql, int (*callback)(void *, int, char **, char **), void *context)
{
	sqlite3* DB;
	char* messageError;
	int exit = sqlite3_open(DB_DIR, &DB);

	exit = sqlite3_exec(DB, sql.c_str(), callback, context, &messageError);
	if (exit != SQLITE_OK) {
		sqlite3_free(messageError);
		return false;
	}
	return true;
}