#include "User.hpp"
using namespace std;

User::User(std::string t_userName, std::string t_userPassword,
           std::string t_userEmail, std::string t_userPhone,
           std::string t_userRemind) {
  m_name = t_userName;
  m_password = t_userPassword;
  m_phone = t_userPhone;
  m_email = t_userEmail;
  m_remind = t_userRemind;
}

User::User(const User &t_user) {
  m_name = t_user.getName();
  m_password = t_user.getPassword();
  m_phone = t_user.getPhone();
  m_email = t_user.getEmail();
  m_remind = t_user.getRemind();
}

std::string User::getName() const { return m_name; }

void User::setName(std::string t_name) { m_name = t_name; }

std::string User::getPassword() const { return m_password; }

void User::setPassword(std::string t_password) { m_password = t_password; }

std::string User::getEmail() const { return m_email; }

void User::setEmail(std::string t_email) { m_email = t_email; }

std::string User::getPhone() const { return m_phone; }

void User::setPhone(std::string t_phone) { m_phone = t_phone; }