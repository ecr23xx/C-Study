#include "Storage.hpp"
#include "Date.hpp"
#include "Path.hpp"
#include <fstream>
#include <iostream>
using namespace std;

std::shared_ptr<Storage> Storage::m_instance = NULL;

Storage::Storage() { readFromFile(); }

// istream& getline (istream& is, string& str, char delim);
// is : The input stream from which a string is to be extracted.
// delim : the line delimiter (defualt as '\n')
bool Storage::readFromFile(void) {
  ifstream inFile;
  inFile.open(Path::userPath);

  while (inFile.good()) {
    string t_userName;
    string t_userPassword;
    string t_userEmail;
    string t_userPhone;
    string t_userRemind;
    string fuck;

    // input stream format as
    // "name","password","email","phoneNumber","remind"
    getline(inFile, fuck, '\"');
    getline(inFile, t_userName, '\"');
    getline(inFile, fuck, '\"');
    getline(inFile, t_userPassword, '\"');
    getline(inFile, fuck, '\"');
    getline(inFile, t_userEmail, '\"');
    getline(inFile, fuck, '\"');
    getline(inFile, t_userPhone, '\"');
    getline(inFile, fuck, '\"');
    getline(inFile, t_userRemind, '\"');

    createUser(User(t_userName, t_userPassword, t_userEmail, t_userPhone,
                    t_userRemind));
  }
  inFile.close();

  ifstream inFile2(Path::meetingPath);
  while (inFile2.good()) {
    // input stream format as
    // "title","sponsor","participator","startTime","endTime"
    string fuck;
    std::string t_sponsor;
    vector<string> t_participator;
    string sp;
    Date t_startTime;
    string sst;
    Date t_endTime;
    string set;
    std::string t_title;

    getline(inFile2, fuck, '\"');
    getline(inFile2, t_sponsor, '\"');
    getline(inFile2, fuck, '\"');

    getline(inFile2, sp, '\"');
    getline(inFile2, fuck, '\"');

    fuck = "";
    if (sp == "")
      continue;
    for (size_t i = 0; i < sp.size(); i++) {
      if (sp[i] != '&') {
        fuck += sp[i];
      } else {
        t_participator.push_back(fuck);
        fuck = "";
      }
    }
    if (fuck != "")
      t_participator.push_back(fuck);

    getline(inFile2, sst, '\"');
    getline(inFile2, fuck, '\"');

    getline(inFile2, set, '\"');
    getline(inFile2, fuck, '\"');

    getline(inFile2, t_title, '\"');

    createMeeting(Meeting(t_sponsor, t_participator, Date::stringToDate(sst),
                          Date::stringToDate(set), t_title));
  }
  inFile2.close();

  return (true);
}

bool Storage::writeToFile(void) {
  ofstream outFile(Path::userPath, ios::out);
  for (auto it = m_userList.begin(); it != m_userList.end(); it++) {
    if (m_userList.size() == 0)
      break;
    outFile << "\"" << (*it).getName() << "\",\"" << (*it).getPassword()
            << "\",\"" << (*it).getEmail() << "\",\"" << (*it).getPhone()
            << "\",\"" << (*it).getRemind() << "\"\n";
  }
  outFile.close();

  ofstream outFile2(Path::meetingPath, ios::out);
  outFile2.clear();
  for (auto it = m_meetingList.begin(); it != m_meetingList.end(); it++) {
    if (m_meetingList.size() == 0)
      break;
    outFile2 << "\"" << (*it).getSponsor() << "\",\"";

    for (size_t i = 0; i < (*it).getParticipator().size() - 1; i++) {
      outFile2 << (*it).getParticipator()[i] << "&";
    }

    outFile2 << (*it).getParticipator()[(*it).getParticipator().size() - 1];

    outFile2 << "\",\"" << Date::dateToString((*it).getStartDate()) << "\",\""
             << Date::dateToString((*it).getEndDate()) << "\",\""
             << (*it).getTitle() << "\"\n";
  }
  outFile2.close();
  return (true);
}

std::shared_ptr<Storage> Storage::getInstance(void) {
  // template <class U> void reset(U* p)
  // p : pointer whose ownership is taken over by the object.
  if (m_instance == NULL)
    m_instance.reset(new Storage());
  m_instance->readFromFile();
  return m_instance;
}

Storage::~Storage() {
  sync();
  m_instance.reset();
}

void Storage::createUser(const User &t_user) {
  for (auto it = m_userList.begin(); it != m_userList.end(); it++) {
    if ((*it).getName() == t_user.getName())
      return;
  }
  m_userList.push_back(t_user);
}

std::list<User>
Storage::queryUser(std::function<bool(const User &)> filter) const {
  list<User> ans;
  int count = 0;
  for (auto it = m_userList.begin(); it != m_userList.end(); it++) {
    if (filter(*it)) {
      ans.push_back(*it);
    }
  }
  return ans;
}

int Storage::updateUser(std::function<bool(const User &)> filter,
                        std::function<void(User &)> switcher) {
  int count = 0;
  for (auto it = m_userList.begin(); it != m_userList.end(); it++) {
    if (filter(*it)) {
      switcher(*it);
      count++;
    }
  }
  return count;
}

int Storage::deleteUser(std::function<bool(const User &)> filter) {
  int count = 0;
  for (auto it = m_userList.begin(); it != m_userList.end(); it++) {
    if (filter(*it)) {
      it = m_userList.erase(it);
      count++;
    }
  }
  return count;
}

void Storage::createMeeting(const Meeting &t_meeting) {
  for (auto it = m_meetingList.begin(); it != m_meetingList.end(); it++) {
    if ((*it).getTitle() == t_meeting.getTitle())
      return;
  }
  m_meetingList.push_back(t_meeting);
}

std::list<Meeting>
Storage::queryMeeting(std::function<bool(const Meeting &)> filter) const {
  list<Meeting> ans;
  int count = 0;
  for (auto it = m_meetingList.begin(); it != m_meetingList.end(); it++) {
    if (filter(*it)) {
      ans.push_back(*it);
    }
  }
  return ans;
}

int Storage::updateMeeting(std::function<bool(const Meeting &)> filter,
                           std::function<void(Meeting &)> switcher) {
  int count = 0;
  for (auto it = m_meetingList.begin(); it != m_meetingList.end(); it++) {
    if (filter(*it)) {
      switcher(*it);
      count++;
    }
  }
  return count;
}

int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter) {
  int count = 0;
  for (auto it = m_meetingList.begin(); it != m_meetingList.end();) {
    if (filter(*it)) {
      it = m_meetingList.erase(it);
      count++;
    } else {
      it++;
    }
  }
  return count;
}

std::string Storage::findPassword(std::function<bool(const User &)> filter) {
  for (auto it = m_userList.begin(); it != m_userList.end(); it++) {
    if (filter(*it)) {
      return (*it).getPassword();
    }
  }
  return string("");
}

bool Storage::sync(void) {
  if (writeToFile() == (true))
    return (true);
  else
    return (false);
}


