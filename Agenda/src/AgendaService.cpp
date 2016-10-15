#include "AgendaService.hpp"
#include <algorithm>
#include <iostream>
using namespace std;

AgendaService::AgendaService() { startAgenda(); }

AgendaService::~AgendaService() { quitAgenda(); }

bool AgendaService::userLogIn(const std::string userName,
                              const std::string password) {
  auto filter = [userName, password](const User &user) -> bool {
    return (user.getName() == userName) && (user.getPassword() == password);
  };
  if (m_storage->queryUser(filter).size() == 0) {
    throw myException("[error] Password is wrong or user doesn't exist");
  } else {
    showRemind(userName);
    return (true);
  }
}

bool AgendaService::userRegister(const std::string userName,
                                 const std::string password,
                                 const std::string email,
                                 const std::string phone) {
  auto filter = [userName, password, email, phone](const User &user) -> bool {
    return (userName == user.getName());
  };
  if (m_storage->queryUser(filter).size() == 0) {
    m_storage->createUser(User(userName, password, email, phone, ""));
    return (true);
  } else {
    throw myException("[error] User's name has been registed");
  }
}

bool AgendaService::deleteUser(const std::string userName,
                               const std::string password) {
  auto filter = [userName, password](const User &user) -> bool {
    return (user.getName() == userName) && (user.getPassword() == password);
  };

  auto filter2 = [userName](const Meeting &meeting) -> bool {
    if (userName == meeting.getSponsor() || meeting.isParticipator(userName))
      return (true);
    else
      return (false);
  };

  if (m_storage->deleteUser(filter)) {
    m_storage->deleteMeeting(filter2);
    return (true);
  } else {
    return (false);
  }
}

std::list<User> AgendaService::listAllUsers(void) const {
  auto filter = [](const User &user) -> bool { return true; };
  return m_storage->queryUser(filter);
}

bool AgendaService::createMeeting(const std::string userName,
                                  const std::string title,
                                  const std::string startDate,
                                  const std::string endDate,
                                  const std::vector<std::string> participator) {
  if (Date::isValid(Date::stringToDate(startDate)) == (false) ||
      Date::isValid(Date::stringToDate(endDate)) == (false))
    return (false);

  // different title
  auto filter1 = [title](const Meeting &meeting) -> bool {
    return meeting.getTitle() == title;
  };

  if (m_storage->queryMeeting(filter1).size() > 0)
    throw myException("[error] This title has been created");

  // sponsor not in userlist
  auto filter2 = [userName](const User &user) -> bool {
    return userName == user.getName();
  };
  if (m_storage->queryUser(filter2).size() <= 0)
    throw myException("[error] The sponsor hasn't registed yet");

  // participator not in userlist
  for (size_t i = 0; i < participator.size(); i++) {
    auto filter3 = [=](const User &user) -> bool {
      return participator[i] == user.getName();
    };
    if (m_storage->queryUser(filter3).size() <= 0)
      throw myException("[error] Some participator hasn't registed yet");
  }
  if (participator.size() == 0)
    throw myException("[error] The sponsor may feel lonely");

  // participator's time
  for (size_t i = 0; i < participator.size(); i++) {
    auto filter5 = [=](const Meeting &meeting) -> bool {
      int flag = 0;
      if (startDate > Date::dateToString(meeting.getStartDate()) &&
          startDate < Date::dateToString(meeting.getEndDate()))
        flag++;
      if (endDate > Date::dateToString(meeting.getStartDate()) &&
          endDate < Date::dateToString(meeting.getEndDate()))
        flag++;
      if (startDate < Date::dateToString(meeting.getStartDate()) &&
          endDate > Date::dateToString(meeting.getEndDate()))
        flag++;
      if (startDate == Date::dateToString(meeting.getStartDate()) ||
          endDate == Date::dateToString(meeting.getEndDate()))
        flag++;

      if (flag > 0 && (meeting.isParticipator(participator[i]) ||
                       participator[i] == meeting.getSponsor())) {
        return (true);
      } else {
        return (false);
      }
    };
    if (m_storage->queryMeeting(filter5).size() > 0)
      throw myException("[error] Some participator has already had a meeting "
                        "during that time");
  }

  // sponsor's time
  auto filter5 = [=](const Meeting &meeting) -> bool {
    int flag = 0;
    if (startDate > Date::dateToString(meeting.getStartDate()) &&
        startDate < Date::dateToString(meeting.getEndDate()))
      flag++;
    if (endDate > Date::dateToString(meeting.getStartDate()) &&
        endDate < Date::dateToString(meeting.getEndDate()))
      flag++;
    if (startDate < Date::dateToString(meeting.getStartDate()) &&
        endDate > Date::dateToString(meeting.getEndDate()))
      flag++;

    if (startDate == Date::dateToString(meeting.getStartDate()) ||
        endDate == Date::dateToString(meeting.getEndDate()))
      flag++;

    if (flag > 0 && (meeting.isParticipator(userName) ||
                     userName == meeting.getSponsor())) {
      return (true);
    } else {
      return (false);
    }
  };
  if (m_storage->queryMeeting(filter5).size() > 0)
    throw myException(
        "[error] The sponsor has already had a meeting during that time");

  // sponsor shall not in participator
  for (size_t i = 0; i < participator.size(); i++)
    if (participator[i] == userName)
      throw myException("[error] The sponsor can't be a participator");

  if (startDate >= endDate)
    throw myException("[error] start-date is beyond end-date");

  m_storage->createMeeting(
      Meeting(userName, participator, startDate, endDate, title));

  string remind("You have been invited to a meeting by ");
  remind += userName;
  remind += " from ";
  remind += startDate;
  remind += " to ";
  remind += endDate;
  remindParticipator(participator, remind);

  return (true);
}

std::list<Meeting> AgendaService::meetingQuery(const std::string userName,
                                               const std::string title) const {
  auto filter = [=](const Meeting &meeting) -> bool {
    if (title == meeting.getTitle() && (userName == meeting.getSponsor() ||
                                        meeting.isParticipator(userName))) {
      return (true);
    } else {
      return (false);
    }
  };

  return m_storage->queryMeeting(filter);
}

std::list<Meeting>
AgendaService::meetingQuery(const std::string userName,
                            const std::string startDate,
                            const std::string endDate) const {
  if (!Date::isValid(Date::stringToDate(startDate)) ||
      !Date::isValid(Date::stringToDate(endDate)) || startDate < endDate) {
    list<Meeting> empty;
    return empty;
  }
  auto filter = [=](const Meeting &meeting) -> bool {
    int flag = 0;
    if (startDate >= Date::dateToString(meeting.getStartDate()) &&
        startDate <= Date::dateToString(meeting.getEndDate()))
      flag++;
    if (endDate >= Date::dateToString(meeting.getStartDate()) &&
        endDate <= Date::dateToString(meeting.getEndDate()))
      flag++;
    if (endDate >= Date::dateToString(meeting.getEndDate()) &&
        startDate <= Date::dateToString(meeting.getStartDate()))
      flag++;
    // if (startDate == Date::dateToString(meeting.getStartDate()) ||
    // 	  endDate == Date::dateToString(meeting.getEndDate()))
    // 	flag++;

    if (flag > 0 && (meeting.isParticipator(userName) ||
                     userName == meeting.getSponsor())) {
      return (true);
    } else {
      return (false);
    }
  };

  return m_storage->queryMeeting(filter);
}

std::list<Meeting>
AgendaService::listAllMeetings(const std::string userName) const {
  auto filter = [=](const Meeting &meeting) -> bool {
    if (userName == meeting.getSponsor())
      return (true);
    if (meeting.isParticipator(userName))
      return (true);
    return (false);
  };

  return m_storage->queryMeeting(filter);
}

std::list<Meeting>
AgendaService::listAllSponsorMeetings(const std::string userName) const {
  auto filter = [=](const Meeting &meeting) -> bool {
    if (userName == meeting.getSponsor())
      return (true);
    else
      return (false);
  };

  return m_storage->queryMeeting(filter);
}

std::list<Meeting>
AgendaService::listAllParticipateMeetings(const std::string userName) const {
  auto filter = [=](const Meeting &meeting) -> bool {
    if (meeting.isParticipator(userName))
      return (true);
    else
      return (false);
  };

  return m_storage->queryMeeting(filter);
}

bool AgendaService::deleteMeeting(const std::string userName,
                                  const std::string title) {
  auto filter = [=](const Meeting &meeting) -> bool {
    if (title == meeting.getTitle() && userName == meeting.getSponsor())
      return (true);
    else
      return (false);
  };

  return (m_storage->deleteMeeting(filter) > 0);
}

bool AgendaService::deleteAllMeetings(const std::string userName) {
  auto filter = [userName](const Meeting &meeting) -> bool {
    if (userName == meeting.getSponsor())
      return (true);
    else
      return (false);
  };

  return (m_storage->deleteMeeting(filter) > 0);
}

bool AgendaService::updateUser(const std::string userName,
                               const std::string password,
                               const std::string email,
                               const std::string phone) {
  auto filter = [userName](const User &user) -> bool {
    return (userName == user.getName());
  };

  auto switcher = [=](User &user) {
    user.setPassword(password);
    user.setEmail(email);
    user.setPhone(phone);
  };

  m_storage->updateUser(filter, switcher);
  return (true);
}

bool AgendaService::findPassword(const std::string userName,
                                 const std::string email,
                                 const std::string phone) {
  auto filter = [=](const User &user) -> bool {
    return (userName == user.getName() && email == user.getEmail() &&
            phone == user.getPhone());
  };

  if (m_storage->findPassword(filter).size() == 0) {
    throw myException("[error] User doesn't exist or information is wrong");
  } else {
    cout << userName << "'s password is " << m_storage->findPassword(filter)
         << endl;
    return (true);
  }
}

void AgendaService::remindParticipator(
    const std::vector<std::string> participator, const std::string remind) {
  for (size_t i = 0; i < participator.size(); i++) {
    auto filter = [=](const User &user) -> bool {
      return (participator[i] == user.getName());
    };

    auto switcher = [remind](User &user) -> void { user.setRemind(remind); };

    m_storage->updateUser(filter, switcher);
  }
}

void AgendaService::showRemind(string userName) {
  auto filter = [userName](const User &user) -> bool {
    return (user.getName() == userName && user.getRemind().size() > 0);
  };

  auto switcher = [](User &user) -> void {
    cout << "[remind] " << user.getRemind() << endl;
    user.setRemind("");
  };

  m_storage->updateUser(filter, switcher);
}

void AgendaService::startAgenda(void) { m_storage = Storage::getInstance(); }

void AgendaService::quitAgenda(void) { m_storage->sync(); }
