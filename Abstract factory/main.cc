#include <memory>
#include <string>
#include <utility>

// Use `Database` interface acts as an aggreated interface is not a good idea,
// because when there's new operations (GetEmail, GetAddress, etc.), all
// inherited classes need to update (add new base abstract function, all derived
// classes need to add accordingly).
//
// Better way is to separate different operations into different interfaces,
// e.g. `UserName` for get/set, `UserEmail` for get/set, `UserAddress` for
// get/set. This kind of design matchs open-close principle, but needs abstract
// factory to create `UserName` interface, `UserEmail` interface, etc.
class Database {
public:
  virtual ~Database() = default;

  virtual std::string GetName(int64_t id) = 0;

  virtual int64_t InsertName(const std::string &name) = 0;
};

class MySqlDatabase : public Database {
public:
  ~MySqlDatabase() override = default;

  std::string GetName(int64_t id) override {
    // Gets user name of `id`.
    return "sql user name";
  }

  int64_t InsertName(const std::string &name) override {
    // Sets user name.
    return 0;
  }
};

class PostgreSqlDaatbase : public Database {
public:
  ~PostgreSqlDaatbase() override = default;

  std::string GetName(int64_t id) override {
    // Gets username of `id`.
    return "postgre sql user name";
  }

  int64_t InsertName(const std::string &name) override {
    // Sets user name;
    return 0;
  }
};

class User {
public:
  explicit User(std::unique_ptr<Database> database)
      : database_(std::move(database)) {}

  std::string GetName(int64_t id) const { return database_->GetName(id); }

  int64_t InsertName(const std::string &name) const {
    return database_->InsertName(name);
  }

private:
  std::unique_ptr<Database> database_;
};

// An independent interface for user name.
class UserNameIntf {
public:
  virtual std::string Get(int64_t id) = 0;
  virtual int64_t Insert(const std::string &name) = 0;
};

// An independent interface for user email.
class UserEmailIntf {
public:
  virtual std::string Get(int64_t id) = 0;
  virtual int64_t Insert(const std::string &name) = 0;
};

// Implements `UserNameIntf` for MySQL.
class MySqlUserName : public UserNameIntf {
public:
  std::string Get(int64_t id) { return "mysql user name"; }

  int64_t Insert(const std::string &name) { return 0; }
};

// Implements `UserNameIntf` for PostgreSQL.
class PostgreSqlUserName : public UserNameIntf {
public:
  std::string Get(int64_t id) { return "postgresql user name"; }

  int64_t Insert(const std::string &name) { return 0; }
};

// Implements `UserEmailIntf` for MySQL.
class MySqlUserEmail : public UserEmailIntf {
public:
  std::string Get(int64_t id) { return "mysql user email "; }

  int64_t Insert(const std::string &name) { return 0; }
};

// Implements `UserEmailIntf` for PostgreSQL.
class PostgreSqlUserEmail : public UserEmailIntf {
public:
  std::string Get(int64_t id) { return "postgresql user email"; }

  int64_t Insert(const std::string &name) { return 0; }
};

// A factory to create interface.
class AbstractFactory {
  enum class DatabaseEnum {
    kMySQL,
    kPostgreSQL,
  };

public:
  explicit AbstractFactory(const std::string &database_type)
      : database_type_(DatabaseType(database_type)) {}

  UserNameIntf *CreateUserName() {
    switch (database_type_) {
    case DatabaseEnum::kMySQL:
      return new MySqlUserName;

    case DatabaseEnum::kPostgreSQL:
      return new PostgreSqlUserName;
    }
  }

  UserEmailIntf *CreateUserEmaill() {
    switch (database_type_) {
    case DatabaseEnum::kMySQL:
      return new MySqlUserEmail;

    case DatabaseEnum::kPostgreSQL:
      return new PostgreSqlUserEmail;
    }
  }

private:
  DatabaseEnum DatabaseType(const std::string& database_type) const {
    if (database_type.compare("mysql") == 0) {
      return DatabaseEnum::kMySQL;
    }
    return DatabaseEnum::kPostgreSQL;
  }

  // Type of database, such as "mysql", "postgresql", etc.
  DatabaseEnum database_type_;
};

int main(int argc, char *argv[]) {
  auto mysql = std::make_unique<MySqlDatabase>();
  User user(std::move(mysql));

  return 0;
}
