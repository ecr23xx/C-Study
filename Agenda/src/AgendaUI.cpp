#include "AgendaUI.hpp"
#include <iomanip>
#include <iostream>
using namespace std;

AgendaUI::AgendaUI() { startAgenda(); }

void AgendaUI::OperationLoop(void) {
  string c;
  cout << "-----------------------Agenda-----------------------" << endl
       << "l   -- log in by username and password" << endl
       << "r   -- register an Agenda account" << endl
       << "h   -- help information" << endl
       << "f   -- find password" << endl
       << "q   -- quit Agenda" << endl
       << "----------------------------------------------------" << endl
       << endl
       << "Agenda : ~$ ";

  while (cin >> c) {
    switch (c[0]) {
    case 'l':
      userLogIn();
      break;
    case 'r':
      userRegister();
      break;
    case 'f':
      findPassword();
      break;
    case 'h':
      cout << "-----------------------Agenda-----------------------" << endl
           << "l   -- log in by username and password" << endl
           << "r   -- register an Agenda account" << endl
           << "h   -- help information" << endl
           << "f   -- find password" << endl
           << "q   -- quit Agenda" << endl
           << "----------------------------------------------------" << endl;
      break;
    case 'q':
      quitAgenda();
      cout << "-----------------------Agenda-----------------------" << endl
           << "Thanks for using agenda, Goodbye!" << endl
           << "----------------------------------------------------" << endl
           << endl;

      return;

    default:
      cerr << "[error] please type in character l, r, q and try again" << endl;
    }
    cout << endl << "Agenda : ~$ ";
  }
}

void AgendaUI::startAgenda(void) { m_agendaService.startAgenda(); }

std::string AgendaUI::getOperation() {
  cout << endl;
  cout << "Agenda@" << m_userName << ":  # ";
  string c;
  cin >> c;
  return c;
}

bool AgendaUI::executeOperation(std::string t_operation) {
  if (t_operation == "o") {
    userLogOut();
    return (false);
  } else if (t_operation == "dc") {
    deleteUser();
    return (false);
  } else if (t_operation == "lu") {
    listAllUsers();
    return (true);
  } else if (t_operation == "cm") {
    createMeeting();
    return (true);
  } else if (t_operation == "la") {
    listAllMeetings();
    return (true);
  } else if (t_operation == "las") {
    listAllSponsorMeetings();
    return (true);
  } else if (t_operation == "lap") {
    listAllParticipateMeetings();
    return (true);
  } else if (t_operation == "qm") {
    queryMeetingByTitle();
    return (true);
  } else if (t_operation == "qt") {
    queryMeetingByTimeInterval();
    return (true);
  } else if (t_operation == "dm") {
    deleteMeetingByTitle();
    return (true);
  } else if (t_operation == "da") {
    deleteAllMeetings();
    return (true);
  } else if (t_operation == "uu") {
    updateUser();
    return (true);
  } else if (t_operation == "h") {
    cout << "-----------------------Agenda-----------------------" << endl;
    cout << "Action :" << endl;
    cout << "o   -- log out Agenda" << endl;
    cout << "dc  -- delete Agenda account" << endl;
    cout << "lu  -- list all Agenda user" << endl;
    cout << "cm  -- creat a meeting" << endl;
    cout << "la  -- list all meetings" << endl;
    cout << "las -- list all sponsor meetings" << endl;
    cout << "lap -- list all participator meetings" << endl;
    cout << "qm  -- query meeting by title" << endl;
    cout << "qt  -- query meeting by time interval" << endl;
    cout << "dm  -- delete meeting by title" << endl;
    cout << "da  -- delete all meetings" << endl;
    cout << "uu  -- update user information" << endl;
    cout << "h   -- help information" << endl;
    cout << "----------------------------------------------------";

    cout << endl;
    return (true);
  } else {
    cerr << "[error] please try again!" << endl;
    return (true);
  }
}

void AgendaUI::findPassword() {
  string un, e, p;
  cout << "[find password] [user name] [email] [phone]" << endl;
  cout << "[find password] ";
  cin >> un >> e >> p;
  try {
    m_agendaService.findPassword(un, e, p);
  } catch (myException &e) {
    cerr << e.what() << endl;
    cerr << "[error] Find failed. Please try again" << endl;
    return;
  }
  cout << "[find password] succeed!" << endl;
}

void AgendaUI::userLogIn(void) {
  cout << "[log in] [user name] [password]" << endl;
  cout << "[log in] ";

  string userName, userPassword;
  cin >> userName >> userPassword;
  try {
    m_agendaService.userLogIn(userName, userPassword);
  } catch (myException &e) {
    cerr << e.what() << endl;
    cerr << "[error] Log in failed. Please try again" << endl;
    return;
  }
  cout << "[log in] succeed!" << endl;
  m_userName = userName;
  m_userPassword = userPassword;
  cout << "-----------------------Agenda-----------------------" << endl;
  cout << "Action :" << endl;
  cout << "o   -- log out Agenda" << endl;
  cout << "dc  -- delete Agenda account" << endl;
  cout << "lu  -- list all Agenda user" << endl;
  cout << "cm  -- creat a meeting" << endl;
  cout << "la  -- list all meetings" << endl;
  cout << "las -- list all sponsor meetings" << endl;
  cout << "lap -- list all participator meetings" << endl;
  cout << "qm  -- query meeting by title" << endl;
  cout << "qt  -- query meeting by time interval" << endl;
  cout << "dm  -- delete meeting by title" << endl;
  cout << "da  -- delete all meetings" << endl;
  cout << "uu  -- update user information" << endl;
  cout << "h   -- help information" << endl;
  cout << "----------------------------------------------------";

  cout << endl;

  while (executeOperation(getOperation()))
    ;
}

void AgendaUI::userRegister(void) {
  cout << "[register] [user name] [password] [email] [phone]" << endl;
  cout << "[register] ";

  string userName, userPassword, userEmail, userPhone;
  cin >> userName >> userPassword >> userEmail >> userPhone;
  try {
    m_agendaService.userRegister(userName, userPassword, userEmail, userPhone);
  } catch (myException &e) {
    cerr << e.what() << endl;
    cerr << "[error] fail! Please try again" << endl;
    return;
  }

  cout << "[register] succeed!" << endl;
}

void AgendaUI::quitAgenda(void) { m_agendaService.quitAgenda(); }

void AgendaUI::userLogOut(void) {
  cout << "[Log out] Goodbye " << m_userName << endl;
  m_userName = m_userPassword = "";
}

void AgendaUI::deleteUser(void) {
  m_agendaService.deleteUser(m_userName, m_userPassword);
  cout << "[delete agenda account] succeed!" << endl;
  userLogOut();
}

void AgendaUI::listAllUsers(void) {
  auto li = m_agendaService.listAllUsers();
  cout << "[list all users]" << endl << endl;
  cout << left;
  cout << setw(15) << "username" << setw(15) << "email" << setw(15) << "phone"
       << endl;
  cout << "---------------------------------------------" << endl;
  for (auto it = li.begin(); it != li.end(); it++) {
    cout << setw(15) << it->getName() << setw(15) << it->getEmail() << setw(15)
         << it->getPhone() << endl;
  }
}

void AgendaUI::createMeeting(void) {
  int num;
  std::vector<string> v;
  string st, et, t;
  cout << "[create meeting] "
       << "[the number of participators]" << endl
       << "[create meeting] ";
  cin >> num;

  for (int i = 0; i < num; i++) {
    string temp;
    cout << "[create meeting] "
         << "[please enter the participator " << i + 1 << " ]" << endl;
    cout << "[create meeting] ";
    cin >> temp;
    v.push_back(temp);
  }
  cout << "[create meeting] "
       << "[title] "
       << "[start time(yyyy-mm-dd/hh:mm)] "
       << "[end time(yyyy-mm-dd/hh:mm)]" << endl;
  cout << "[create meeting] ";
  cin >> t >> st >> et;

  try {
    m_agendaService.createMeeting(m_userName, t, st, et, v);
  } catch (myException &e) {
    cerr << e.what() << endl;
    cerr << "[error] Creation failed. Please try again" << endl;
    return;
  }

  cout << "[create meeting] succeed!" << endl;
}

void AgendaUI::listAllMeetings(void) {
  auto li = m_agendaService.listAllMeetings(m_userName);
  cout << "[list all meetings]" << endl << endl;

  printMeetings(li);
}

void AgendaUI::listAllSponsorMeetings(void) {
  auto li = m_agendaService.listAllSponsorMeetings(m_userName);
  cout << "[list all sponsor meetings]" << endl << endl;

  printMeetings(li);
}

void AgendaUI::listAllParticipateMeetings(void) {
  auto li = m_agendaService.listAllParticipateMeetings(m_userName);
  cout << "[list allparticipate meetings]" << endl << endl;

  printMeetings(li);
}

void AgendaUI::queryMeetingByTitle(void) {
  string t;
  cout << "[query meeting] [title]" << endl;
  cout << "[query meeting] ";
  cin >> t;

  auto li = m_agendaService.meetingQuery(m_userName, t);
  cout << endl;
  printMeetings(li);
}

void AgendaUI::queryMeetingByTimeInterval(void) {
  string st, et;
  cout << "[query meeting] [start time(yyyy-mm-dd/hh:mm)] "
       << "[end time(yyyy-mm-dd/hh:mm)]" << endl
       << "[query meeting] ";
  cin >> st >> et;

  auto li = m_agendaService.meetingQuery(m_userName, st, et);
  cout << endl;
  printMeetings(li);
}

void AgendaUI::deleteMeetingByTitle(void) {
  string t;
  cout << "[delete meeting] [title]" << endl;
  cout << "[delete meeting] ";
  cin >> t;

  if (m_agendaService.deleteMeeting(m_userName, t))
    cout << "[delete meeting by title] succeed!" << endl;
  else
    cerr << "[error] delete meeting fail" << endl;
}

void AgendaUI::deleteAllMeetings(void) {
  cout << "[delete all meetings] ";

  if (m_agendaService.deleteAllMeetings(m_userName))
    cout << "succeed!" << endl;
  else
    cerr << "fail" << endl;
}

void AgendaUI::updateUser() {
  string s;
  cout << "[update user] [old password]" << endl;
  cout << "[update user] ";
  cin >> s;
  if (s == m_userPassword) {
    string pw, em, p;
    cout << "[update user] Please type in new account information" << endl;
    cout << "[update user] [new password] [new email] [new phone]" << endl;
    cout << "[update user] ";
    cin >> pw >> em >> p;
    m_agendaService.updateUser(m_userName, pw, em, p);
    cout << "[update user] Succeed!" << endl;
  } else {
    cerr << "[error] Old password is wrong" << endl;
    cerr << "[error] Please try again" << endl;
  }
}

void AgendaUI::printMeetings(std::list<Meeting> t_meetings) {
  cout << left;
  cout << setw(15) << "title" << setw(15) << "sponsor" << setw(18)
       << "start_time" << setw(18) << "end_time" << setw(18) << "participators"
       << endl;
  cout << "--------------------------------------------------------------------"
          "------------"
       << endl;

  for (auto it = t_meetings.begin(); it != t_meetings.end(); it++) {
    cout << setw(15) << it->getTitle() << setw(15) << it->getSponsor()
         << setw(18) << Date::dateToString(it->getStartDate()) << setw(18)
         << Date::dateToString(it->getEndDate());
    auto p = it->getParticipator();
    auto it2 = p.begin();
    cout << left;
    cout << *it2++;
    for (; it2 != p.end(); it2++) {
      cout << "," << *it2;
    }
    cout << endl;
  }
}
