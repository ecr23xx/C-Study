#include "JobManager.h"
#include <algorithm>
#include <vector>

JobManager* JobManager::instance = NULL;

bool fun(Job* a, Job* b) {
    if (a->getPriority() < b->getPriority()) return (false);
    if (a->getPriority() > b->getPriority()) return (true);
    return (a->getId() < b->getId());
}

JobManager* JobManager::getInstance() {
    if (instance == NULL) {
        instance = new JobManager();
        return instance;
    } else {
        return instance;
    }
}

bool JobManager::deleteInstance() {
    if (instance == NULL) {
        return (false);
    } else {
        delete instance;
        instance = NULL;
        return (true);
    }
}

void JobManager::addJob(int priority) {
    if (jobFrontPointer == NULL) {
        jobFrontPointer = new Job(priority);
    } else {
        Job* p = jobFrontPointer;
        Job* q = new Job(priority);
        while (p->getNext() != NULL) {
            p = p->getNext();
        }
        p->setNext(q);
    }
}

void JobManager::finishOneJob() {
    if (getNumOfJob() > 1) {
        Job* p = jobFrontPointer;
        jobFrontPointer = jobFrontPointer->getNext();
        delete p;
    } else if (getNumOfJob() == 1) {
        delete jobFrontPointer;
        jobFrontPointer = NULL;
    } else {
        return;
    }
}

void JobManager::sortJob() {
    Job* p = jobFrontPointer;
    vector<Job*> v;
    while (p) {
        v.push_back(p);
        p = p->getNext();
    }
    sort(v.begin(), v.end(), fun);
    jobFrontPointer = *(v.begin());
    vector<Job*>::iterator i = v.begin();
    while (i+1 != v.end()) {
        (*i)->setNext(*(i+1));
        i++;
    }
    (*i)->setNext(NULL);
}

void JobManager::printJob() {
    if (jobFrontPointer == NULL) {
        cout << "empty!" << endl;
    } else {
        Job* p = jobFrontPointer;
        while (p->getNext() != NULL) {
            cout << p->toString() << "->";
            p = p->getNext();
        }
        cout << p->toString() << endl;
    }
}

int JobManager::getNumOfJob() {
    int num = 1;
    Job* p = jobFrontPointer;
    if (p ==  NULL) {
        num = 0;
    } else {
        while (p->getNext() != NULL) {
            p = p->getNext();
            num++;
        }
    }
    return num;
}

void JobManager::clear() {
    while (jobFrontPointer->getNext() != NULL) {
        Job* p = jobFrontPointer->getNext();
        delete jobFrontPointer;
        jobFrontPointer = p;
    }
    delete jobFrontPointer;
    jobFrontPointer = NULL;
}

JobManager::~JobManager() {
    if (jobFrontPointer != NULL)
        clear();
}

JobManager::JobManager() {
    jobFrontPointer = NULL;
}
