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
	sqlite3* DB;
	char *messageError;
	int exit = 0;

	exit = sqlite3_open(_dir.c_str(), &DB);
	std::string sql = "CREATE TABLE IF NOT EXISTS USER("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"PSEUDO TEXT NOT NULL UNIQUE, "
		"PASSWORD TEXT NOT NULL, "
		"ADDRESS	TEXT NOT NULL);";
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in createTable function." << std::endl;
		sqlite3_free(messageError);
	}
	sql = "CREATE TABLE IF NOT EXISTS CONTACT("
		"IDFROM INTEGER, "
		"IDTO INTEGER, "
		"FOREIGN KEY(IDFROM) REFERENCES USER(ID), "
		"FOREIGN KEY(IDTO) REFERENCES USER(ID));";
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in createTable function. 2" << std::endl;
		sqlite3_free(messageError);
	}
	sqlite3_close(DB);
}

Asqlite3::~Asqlite3()
{
}

bool Asqlite3::uploadData(struct User user)
{
	sqlite3* DB;
	char* messageError;

	std::string sql("INSERT INTO USER (PSEUDO, PASSWORD, ADDRESS)"
	"VALUES('" + user.username + "', '" + user.password + "', '" + user.address + "');");

	int exit = sqlite3_open(_dir.c_str(), &DB);
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in upload new user" << std::endl;
		sqlite3_free(messageError);
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
	sqlite3* DB;
	char* messageError;

	std::string sql = "SELECT PSEUDO FROM USER WHERE PSEUDO = '" + user.username + "';";
	this->_res.clear();
	int exit = sqlite3_open(_dir.c_str(), &DB);
	exit = sqlite3_exec(DB, sql.c_str(), callbackUserExist, this, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in login function.1" << messageError << std::endl;
		sqlite3_free(messageError);
	}
	if (user.username != this->_res) {
		return USER_NOT_EXIST;
	}
	this->_res.clear();
	sql = "SELECT PSEUDO FROM USER WHERE PASSWORD = '" + user.password + "' AND PSEUDO = '" + user.username + "';";
	exit = sqlite3_exec(DB, sql.c_str(), callbackUserExist, this, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in login function.2" << std::endl;
		sqlite3_free(messageError);
	}
	if (user.username != this->_res) {
		return BAD_PASSWORD;
	}
	this->_res.clear();
	return SUCCESS;
}

std::string Asqlite3::getUser(std::string name)
{
	sqlite3* DB;
	char* messageError;

	std::string sql = "SELECT PSEUDO FROM USER WHERE PSEUDO LIKE '" + name + "%';";
	this->_res.clear();
	int exit = sqlite3_open(_dir.c_str(), &DB);
	exit = sqlite3_exec(DB, sql.c_str(), callbackGetUser, this, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in getUser function." << messageError << std::endl;
		sqlite3_free(messageError);
	}
	return this->_res;
}

bool Asqlite3::linkUser(std::string from, std::string to)
{
	sqlite3* DB;
	char* messageError;
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
	std::string sql = "INSERT INTO CONTACT(IDFROM, IDTO) VALUES(" + idfrom + ", " + idto + ");";
	std::cout << sql;
	int exit = sqlite3_open(_dir.c_str(), &DB);
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in linkUser function." << messageError << std::endl;
		sqlite3_free(messageError);
		return false;
	}
	return true;
}

std::string Asqlite3::getIdByUsername(std::string username)
{
	sqlite3* DB;
	char* messageError;

	std::string sql = "SELECT ID FROM USER WHERE PSEUDO = '" + username + "';";
	this->_res.clear();
	int exit = sqlite3_open(_dir.c_str(), &DB);
	exit = sqlite3_exec(DB, sql.c_str(), callbackUserExist, this, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in getid function." << std::endl;
		sqlite3_free(messageError);
	}
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
	sqlite3* DB;
	char* messageError;
	std::string id = getIdByUsername(username);
	std::string sql = "SELECT PSEUDO, ADDRESS "
		"FROM CONTACT "
		"INNER JOIN USER ON USER.ID=CONTACT.IDFROM OR USER.ID=CONTACT.IDTO "
		"WHERE USER.ID != "+id+" AND (CONTACT.IDFROM = "+id+" OR CONTACT.IDTO = "+id+")";
	int exit = sqlite3_open(_dir.c_str(), &DB);
	this->_linkedUser.clear();
	exit = sqlite3_exec(DB, sql.c_str(), callbackFillContact, this, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in getid function." << std::endl;
		sqlite3_free(messageError);
	}
	for (auto user : this->_linkedUser)
		std::cout << user.username << " " << user.address << std::endl;
	return this->_linkedUser;
}