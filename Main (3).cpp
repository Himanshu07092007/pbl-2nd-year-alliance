#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cctype>
class PG {
public:
    int id;
    char name[50];
    char location[50];
    double rent;
    char gender[15];
    bool foodAvailable;
    bool wifiAvailable;
    bool acAvailable;
    double distance;
    double rating;
    PG();
    PG(int pId, const char* pName, const char* pLoc, double pRent,
       const char* pGen, bool food, bool wifi, bool ac, double dist, double rate);
    void displayCard() const;
    void displayRow() const;
    bool operator<(const PG& other) const {
        return this->rent < other.rent;
    }
    bool operator>(const PG& other) const {
        return this->rent > other.rent;
    }
    bool operator==(int targetId) const {
        return this->id == targetId;
    }
};
PG::PG() {
    id = 0;
    name[0] = '\0';
    location[0] = '\0';
    rent = 0.0;
    gender[0] = '\0';
    foodAvailable = false;
    wifiAvailable = false;
    acAvailable = false;
    distance = 0.0;
    rating = 0.0;
}
PG::PG(int pId, const char* pName, const char* pLoc, double pRent,
       const char* pGen, bool food, bool wifi, bool ac, double dist, double rate) {
    id = pId;
    strncpy(name, pName, sizeof(name) - 1);
    name[sizeof(name) - 1] = '\0';
    strncpy(location, pLoc, sizeof(location) - 1);
    location[sizeof(location) - 1] = '\0';
    rent = pRent;
    strncpy(gender, pGen, sizeof(gender) - 1);
    gender[sizeof(gender) - 1] = '\0';
    foodAvailable = food;
    wifiAvailable = wifi;
    acAvailable = ac;
    distance = dist;
    rating = rate;
}
void PG::displayCard() const {
    std::cout << "--------------------------------------------------\n";
    std::cout << "PG ID        : " << id << "\n";
    std::cout << "PG Name      : " << name << "\n";
    std::cout << "Location     : " << location << "\n";
    std::cout << "Rent         : Rs. " << std::fixed << std::setprecision(0) << rent << " / month\n";
    std::cout << "Gender       : " << gender << "\n";
    std::cout << "Food         : " << (foodAvailable ? "Yes" : "No") << "\n";
    std::cout << "Wi-Fi        : " << (wifiAvailable ? "Yes" : "No") << "\n";
    std::cout << "AC           : " << (acAvailable ? "Yes" : "No") << "\n";
    std::cout << "Distance     : " << std::setprecision(1) << distance << " km from college\n";
    std::cout << "Rating       : " << rating << " / 5.0 stars\n";
    std::cout << "--------------------------------------------------\n";
}
void PG::displayRow() const {
    std::string shortName = name;
    if (shortName.length() > 21) shortName = shortName.substr(0, 19) + "..";
    std::string shortLocation = location;
    if (shortLocation.length() > 14) shortLocation = shortLocation.substr(0, 12) + "..";
    std::cout << "| " << std::setw(4) << std::right << id << " | "
              << std::setw(21) << std::left << shortName << " | "
              << std::setw(14) << shortLocation << " | Rs."
              << std::setw(6) << std::right << std::fixed << std::setprecision(0) << rent << " | "
              << std::setw(6) << gender << " | "
              << std::setw(4) << (foodAvailable ? "Yes" : "No") << " | "
              << std::setw(4) << (wifiAvailable ? "Yes" : "No") << " | "
              << std::setw(3) << (acAvailable ? "Yes" : "No") << " | "
              << std::setw(4) << std::setprecision(1) << distance << " km | "
              << std::setw(4) << rating << " |\n";
}
void printTableDivider() {
    std::cout << "+------+-----------------------+----------------+-----------+--------+------+------+-----+---------+------+\n";
}
void printTableHeader() {
    printTableDivider();
    std::cout << "| ID   | PG Name               | Location       | Rent/Mo   | Gender | Food | WiFi | AC  | Dist    | Rate |\n";
    printTableDivider();
}
void displayAllPGRecords(const PG list[], int count) {
    if (count <= 0) {
        std::cout << "\n[Notice] No PG records available to display.\n";
        std::cout << "         Add PGs to pg.txt (one PG per line) and run the program again.\n";
        return;
    }
    printTableHeader();
    for (int i = 0; i < count; i++) {
        list[i].displayRow();
    }
    printTableDivider();
    std::cout << "Total Available PGs: " << count << "\n";
}
static void createSeedDataFile(const char* filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) return;
    outFile << "101|Green Valley PG|Clement Town|7500|Boys|1|1|1|1.5|4.5\n";
    outFile << "102|Sunrise Residency|Subhash Nagar|6000|Boys|1|1|0|2.0|4.0\n";
    outFile << "103|Starlight Girls Haven|ISBT|8500|Girls|1|1|1|3.5|4.7\n";
    outFile << "104|Comfort Stay PG|Mohabewala|5000|Boys|0|1|0|4.2|3.8\n";
    outFile << "105|Elite Comfort PG|Clement Town|9500|Unisex|1|1|1|1.2|4.8\n";
    outFile << "106|Royal Palace PG|Subhash Nagar|11000|Boys|1|1|1|0.8|4.6\n";
    outFile << "107|Shree Ganesh PG|ISBT|5500|Boys|1|0|0|5.5|3.9\n";
    outFile << "108|Tulip Girls Hostel|Mohabewala|7000|Girls|1|1|0|2.8|4.2\n";
    outFile << "109|Metro View PG|Clement Town|8000|Unisex|0|1|1|3.0|4.1\n";
    outFile << "110|Balaji Budget Stay|Subhash Nagar|4500|Boys|0|0|0|6.0|3.5\n";
    outFile << "111|Aura Luxury PG|ISBT|12000|Girls|1|1|1|1.0|4.9\n";
    outFile << "112|City Light PG|Mohabewala|6500|Unisex|1|1|0|2.2|4.3\n";
    outFile.close();
}
static std::string trimText(const std::string& text) {
    size_t start = 0;
    size_t end = text.length();
    while (start < end && (text[start] == ' ' || text[start] == '\t' || text[start] == '\r')) start++;
    while (end > start && (text[end - 1] == ' ' || text[end - 1] == '\t' || text[end - 1] == '\r')) end--;
    return text.substr(start, end - start);
}
static bool isWholeNumber(const std::string& text) {
    if (text.empty()) return false;
    for (size_t i = 0; i < text.length(); i++) {
        if (!isdigit((unsigned char)text[i])) return false;
    }
    return true;
}
static bool isDecimalNumber(const std::string& text) {
    int digits = 0;
    int dots = 0;
    for (size_t i = 0; i < text.length(); i++) {
        if (isdigit((unsigned char)text[i])) digits++;
        else if (text[i] == '.') dots++;
        else return false;
    }
    return digits > 0 && dots <= 1;
}
static bool readYesNoField(const std::string& text, bool& value) {
    std::string lower = text;
    for (size_t i = 0; i < lower.length(); i++) {
        lower[i] = (char)tolower((unsigned char)lower[i]);
    }
    if (lower == "1" || lower == "yes" || lower == "true") { value = true; return true; }
    if (lower == "0" || lower == "no" || lower == "false") { value = false; return true; }
    return false;
}
static bool readGenderField(const std::string& text, std::string& value) {
    std::string lower = text;
    for (size_t i = 0; i < lower.length(); i++) {
        lower[i] = (char)tolower((unsigned char)lower[i]);
    }
    if (lower == "boys") { value = "Boys"; return true; }
    if (lower == "girls") { value = "Girls"; return true; }
    if (lower == "unisex") { value = "Unisex"; return true; }
    return false;
}
static void reportBadLine(const char* filename, int lineNumber, const char* reason) {
    std::cout << "[" << filename << "] Line " << lineNumber << " skipped: " << reason << "\n";
}
int loadPGDataFromFile(PG destinationArray[], int maxCapacity, const char* filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cout << "[Notice] \"" << filename << "\" was not found in the current folder.\n";
        createSeedDataFile(filename);
        inFile.open(filename);
        if (!inFile.is_open()) {
            std::cout << "[File Error] Could not create \"" << filename << "\". No PGs were loaded.\n";
            return 0;
        }
        std::cout << "         A new \"" << filename << "\" with 12 sample PGs was created.\n";
    }
    int count = 0;
    int skipped = 0;
    int lineNumber = 0;
    std::string line;
    while (std::getline(inFile, line)) {
        lineNumber++;
        if (lineNumber == 1 && line.length() >= 3 &&
            (unsigned char)line[0] == 0xEF &&
            (unsigned char)line[1] == 0xBB &&
            (unsigned char)line[2] == 0xBF) {
            line = line.substr(3);
        }
        line = trimText(line);
        if (line.empty() || line[0] == '#') continue;
        if (count >= maxCapacity) {
            std::cout << "[" << filename << "] Only the first " << maxCapacity
                      << " PGs were loaded. The remaining lines were ignored.\n";
            break;
        }
        std::stringstream ss(line);
        std::string token;
        std::string fields[10];
        int fieldCount = 0;
        while (std::getline(ss, token, '|')) {
            if (fieldCount < 10) fields[fieldCount] = trimText(token);
            fieldCount++;
        }
        if (fieldCount != 10) {
            reportBadLine(filename, lineNumber, "expected 10 fields separated by '|'");
            skipped++;
            continue;
        }
        try {
            if (!isWholeNumber(fields[0]) || fields[0].length() > 9 || std::stoi(fields[0]) <= 0) {
                reportBadLine(filename, lineNumber, "PG ID must be a positive whole number");
                skipped++;
                continue;
            }
            int id = std::stoi(fields[0]);
            bool duplicate = false;
            for (int i = 0; i < count; i++) {
                if (destinationArray[i] == id) duplicate = true;
            }
            if (duplicate) {
                reportBadLine(filename, lineNumber, "this PG ID is already used by an earlier line");
                skipped++;
                continue;
            }
            if (fields[1].empty() || fields[2].empty()) {
                reportBadLine(filename, lineNumber, "PG name and location cannot be empty");
                skipped++;
                continue;
            }
            if (!isDecimalNumber(fields[3]) || std::stod(fields[3]) <= 0.0) {
                reportBadLine(filename, lineNumber, "rent must be a number greater than 0");
                skipped++;
                continue;
            }
            double rent = std::stod(fields[3]);
            std::string gender;
            if (!readGenderField(fields[4], gender)) {
                reportBadLine(filename, lineNumber, "gender must be Boys, Girls or Unisex");
                skipped++;
                continue;
            }
            bool food = false, wifi = false, ac = false;
            if (!readYesNoField(fields[5], food) ||
                !readYesNoField(fields[6], wifi) ||
                !readYesNoField(fields[7], ac)) {
                reportBadLine(filename, lineNumber, "Food, WiFi and AC must be 1 (Yes) or 0 (No)");
                skipped++;
                continue;
            }
            if (!isDecimalNumber(fields[8])) {
                reportBadLine(filename, lineNumber, "distance must be a number of km (0 or more)");
                skipped++;
                continue;
            }
            double dist = std::stod(fields[8]);
            if (!isDecimalNumber(fields[9]) || std::stod(fields[9]) > 5.0) {
                reportBadLine(filename, lineNumber, "rating must be a number from 0 to 5");
                skipped++;
                continue;
            }
            double rating = std::stod(fields[9]);
            destinationArray[count] = PG(id, fields[1].c_str(), fields[2].c_str(), rent,
                                         gender.c_str(), food, wifi, ac, dist, rating);
            count++;
        } catch (...) {
            reportBadLine(filename, lineNumber, "a number in this line is too large");
            skipped++;
        }
    }
    inFile.close();
    std::cout << "[" << filename << "] Loaded " << count << " PG(s)";
    if (skipped > 0) std::cout << ", skipped " << skipped << " incorrect line(s)";
    std::cout << ".\n";
    if (count == 0) {
        std::cout << "[Notice] No valid PG records found. Each line must look like:\n"
                  << "         101|Green Valley PG|Knowledge Park|7500|Boys|1|1|1|1.5|4.5\n";
    }
    return count;
}
class Person {
protected:
    char name[50];
    char contact[20];
public:
    Person();
    Person(const char* pName, const char* pContact);
    virtual ~Person();
    virtual void displayInfo() const;
    virtual const char* getRole() const;
    const char* getName() const;
    const char* getContact() const;
};
class StudentUser : public Person {
private:
    char collegeName[50];
    int targetPGId;
public:
    StudentUser();
    StudentUser(const char* pName, const char* pContact, const char* pCollege, int pgId);
    virtual ~StudentUser();
    void displayInfo() const override;
    const char* getRole() const override;
    int getTargetPGId() const;
    const char* getCollegeName() const;
};
Person::Person() {
    name[0] = '\0';
    contact[0] = '\0';
}
Person::Person(const char* pName, const char* pContact) {
    strncpy(name, pName, sizeof(name) - 1);
    name[sizeof(name) - 1] = '\0';
    strncpy(contact, pContact, sizeof(contact) - 1);
    contact[sizeof(contact) - 1] = '\0';
}
Person::~Person() {}
void Person::displayInfo() const {
    std::cout << "[" << getRole() << "] Name: " << name << " | Contact: " << contact;
}
const char* Person::getRole() const {
    return "General Person";
}
const char* Person::getName() const {
    return name;
}
const char* Person::getContact() const {
    return contact;
}
StudentUser::StudentUser() : Person() {
    collegeName[0] = '\0';
    targetPGId = 0;
}
StudentUser::StudentUser(const char* pName, const char* pContact, const char* pCollege, int pgId)
    : Person(pName, pContact) {
    strncpy(collegeName, pCollege, sizeof(collegeName) - 1);
    collegeName[sizeof(collegeName) - 1] = '\0';
    targetPGId = pgId;
}
StudentUser::~StudentUser() {}
const char* StudentUser::getRole() const {
    return "Student Applicant";
}
void StudentUser::displayInfo() const {
    std::cout << "[" << getRole() << "] Name: " << name << " | Phone: " << contact
              << " | College: " << collegeName << " | Target PG ID: #" << targetPGId;
}
int StudentUser::getTargetPGId() const {
    return targetPGId;
}
const char* StudentUser::getCollegeName() const {
    return collegeName;
}
struct ListNode {
    PG data;
    double matchScore;
    ListNode* next;
    ListNode(const PG& pg, double score = 0.0) : data(pg), matchScore(score), next(nullptr) {}
};
class PGLinkedList {
private:
    ListNode* head;
    int count;
public:
    PGLinkedList();
    ~PGLinkedList();
    PGLinkedList(const PGLinkedList&) = delete;
    PGLinkedList& operator=(const PGLinkedList&) = delete;
    bool isEmpty() const;
    int getCount() const;
    void insertEnd(const PG& pg, double score = 0.0);
    bool deleteById(int targetId);
    ListNode* search(int targetId) const;
    ListNode* search(const char* nameQuery) const;
    ListNode* searchById(int targetId) const;
    void displayList() const;
    void displayList(int topN) const;
    ListNode* operator[](int index) const;
    void clear();
    ListNode* getHead() const;
};
PGLinkedList::PGLinkedList() : head(nullptr), count(0) {}
PGLinkedList::~PGLinkedList() {
    clear();
}
bool PGLinkedList::isEmpty() const {
    return head == nullptr;
}
int PGLinkedList::getCount() const {
    return count;
}
ListNode* PGLinkedList::getHead() const {
    return head;
}
void PGLinkedList::insertEnd(const PG& pg, double score) {
    ListNode* newNode = new ListNode(pg, score);
    if (head == nullptr) {
        head = newNode;
    } else {
        ListNode* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    count++;
}
bool PGLinkedList::deleteById(int targetId) {
    if (head == nullptr) return false;
    if (head->data.id == targetId) {
        ListNode* toDelete = head;
        head = head->next;
        delete toDelete;
        count--;
        return true;
    }
    ListNode* curr = head;
    while (curr->next != nullptr && curr->next->data.id != targetId) {
        curr = curr->next;
    }
    if (curr->next != nullptr) {
        ListNode* toDelete = curr->next;
        curr->next = curr->next->next;
        delete toDelete;
        count--;
        return true;
    }
    return false;
}
ListNode* PGLinkedList::search(int targetId) const {
    ListNode* temp = head;
    while (temp != nullptr) {
        if (temp->data == targetId) return temp;
        temp = temp->next;
    }
    return nullptr;
}
ListNode* PGLinkedList::search(const char* nameQuery) const {
    if (!nameQuery || nameQuery[0] == '\0') return nullptr;
    size_t queryLen = strlen(nameQuery);
    ListNode* temp = head;
    while (temp != nullptr) {
        size_t nameLen = strlen(temp->data.name);
        if (nameLen >= queryLen) {
            for (size_t s = 0; s <= nameLen - queryLen; s++) {
                bool match = true;
                for (size_t k = 0; k < queryLen; k++) {
                    if (tolower((unsigned char)temp->data.name[s + k]) != tolower((unsigned char)nameQuery[k])) {
                        match = false;
                        break;
                    }
                }
                if (match) return temp;
            }
        }
        temp = temp->next;
    }
    return nullptr;
}
ListNode* PGLinkedList::searchById(int targetId) const {
    return search(targetId);
}
ListNode* PGLinkedList::operator[](int index) const {
    if (index < 0 || index >= count) return nullptr;
    ListNode* curr = head;
    for (int i = 0; i < index && curr != nullptr; i++) {
        curr = curr->next;
    }
    return curr;
}
void PGLinkedList::displayList() const {
    displayList(count);
}
void PGLinkedList::displayList(int topN) const {
    if (head == nullptr) {
        std::cout << "\n[Linked List] Result list is currently empty. Run a search first.\n";
        return;
    }
    int limit = (topN < count && topN > 0) ? topN : count;
    std::cout << "\n========== CURRENT SEARCH RESULTS (SINGLY LINKED LIST) ==========\n";
    std::cout << "Displaying " << limit << " of " << count << " result(s):\n";
    for (int i = 0; i < limit; i++) {
        ListNode* node = (*this)[i];
        if (!node) break;
        std::cout << "[Node " << (i + 1) << "]";
        if (node->matchScore > 0.0) {
            std::cout << " (Match Score: " << std::fixed << std::setprecision(1) << node->matchScore << " / 100)";
        }
        std::cout << "\n";
        node->data.displayCard();
    }
    std::cout << "Total Nodes in Linked List: " << count << "\n";
}
void PGLinkedList::clear() {
    ListNode* curr = head;
    while (curr != nullptr) {
        ListNode* nextNode = curr->next;
        delete curr;
        curr = nextNode;
    }
    head = nullptr;
    count = 0;
}
struct SearchHistoryRecord {
    char searchTitle[50];
    char criteriaDetails[100];
    int resultCount;
    SearchHistoryRecord();
    SearchHistoryRecord(const char* title, const char* details, int count);
};
class SearchStack {
private:
    static const int MAX_STACK_SIZE = 25;
    SearchHistoryRecord elements[MAX_STACK_SIZE];
    int topIndex;
public:
    SearchStack();
    bool isEmpty() const;
    bool isFull() const;
    int getSize() const;
    bool push(const SearchHistoryRecord& record);
    bool pop(SearchHistoryRecord& poppedRecord);
    bool peek(SearchHistoryRecord& topRecord) const;
    void displayHistory() const;
};
SearchHistoryRecord::SearchHistoryRecord() {
    searchTitle[0] = '\0';
    criteriaDetails[0] = '\0';
    resultCount = 0;
}
SearchHistoryRecord::SearchHistoryRecord(const char* title, const char* details, int count) {
    strncpy(searchTitle, title, sizeof(searchTitle) - 1);
    searchTitle[sizeof(searchTitle) - 1] = '\0';
    strncpy(criteriaDetails, details, sizeof(criteriaDetails) - 1);
    criteriaDetails[sizeof(criteriaDetails) - 1] = '\0';
    resultCount = count;
}
SearchStack::SearchStack() : topIndex(-1) {}
bool SearchStack::isEmpty() const {
    return topIndex == -1;
}
bool SearchStack::isFull() const {
    return topIndex == MAX_STACK_SIZE - 1;
}
int SearchStack::getSize() const {
    return topIndex + 1;
}
bool SearchStack::push(const SearchHistoryRecord& record) {
    if (isFull()) {
        std::cout << "[Stack Overflow] Search history is full (25 searches). Use Undo to free space.\n";
        return false;
    }
    elements[++topIndex] = record;
    return true;
}
bool SearchStack::pop(SearchHistoryRecord& poppedRecord) {
    if (isEmpty()) {
        return false;
    }
    poppedRecord = elements[topIndex--];
    return true;
}
bool SearchStack::peek(SearchHistoryRecord& topRecord) const {
    if (isEmpty()) return false;
    topRecord = elements[topIndex];
    return true;
}
void SearchStack::displayHistory() const {
    if (isEmpty()) {
        std::cout << "\n[Search Stack] History is empty. No searches done yet.\n";
        return;
    }
    std::cout << "\n================ SEARCH HISTORY STACK (LIFO) ================\n";
    for (int i = topIndex; i >= 0; i--) {
        std::cout << "  [Step " << (i + 1) << (i == topIndex ? " (TOP)] " : "]      ")
                  << elements[i].searchTitle << "\n"
                  << "    Criteria: " << elements[i].criteriaDetails << "\n"
                  << "    Matches : " << elements[i].resultCount << " PG(s) found\n"
                  << "  --------------------------------------------------------\n";
    }
}
struct QueueNode {
    StudentUser student;
    int requestId;
    QueueNode* next;
    QueueNode(const StudentUser& s, int reqId) : student(s), requestId(reqId), next(nullptr) {}
};
class VisitQueue {
private:
    QueueNode* frontNode;
    QueueNode* rearNode;
    int count;
public:
    VisitQueue();
    ~VisitQueue();
    VisitQueue(const VisitQueue&) = delete;
    VisitQueue& operator=(const VisitQueue&) = delete;
    bool isEmpty() const;
    int getCount() const;
    void enqueue(const StudentUser& user, int reqId);
    bool dequeue(StudentUser& userOut, int& reqIdOut);
    bool peek(StudentUser& userOut, int& reqIdOut) const;
    void displayQueue() const;
};
VisitQueue::VisitQueue() : frontNode(nullptr), rearNode(nullptr), count(0) {}
VisitQueue::~VisitQueue() {
    while (!isEmpty()) {
        StudentUser dummyUser;
        int dummyId;
        dequeue(dummyUser, dummyId);
    }
}
bool VisitQueue::isEmpty() const {
    return frontNode == nullptr;
}
int VisitQueue::getCount() const {
    return count;
}
void VisitQueue::enqueue(const StudentUser& user, int reqId) {
    QueueNode* newNode = new QueueNode(user, reqId);
    if (rearNode == nullptr) {
        frontNode = rearNode = newNode;
    } else {
        rearNode->next = newNode;
        rearNode = newNode;
    }
    count++;
}
bool VisitQueue::dequeue(StudentUser& userOut, int& reqIdOut) {
    if (isEmpty()) {
        return false;
    }
    QueueNode* temp = frontNode;
    userOut = temp->student;
    reqIdOut = temp->requestId;
    frontNode = frontNode->next;
    if (frontNode == nullptr) {
        rearNode = nullptr;
    }
    delete temp;
    count--;
    return true;
}
bool VisitQueue::peek(StudentUser& userOut, int& reqIdOut) const {
    if (isEmpty()) return false;
    userOut = frontNode->student;
    reqIdOut = frontNode->requestId;
    return true;
}
void VisitQueue::displayQueue() const {
    if (isEmpty()) {
        std::cout << "\n[Visit Queue] You have no booked PG visits.\n";
        return;
    }
    std::cout << "\n================ YOUR BOOKED PG VISITS (QUEUE - FIFO) ================\n";
    QueueNode* curr = frontNode;
    int position = 1;
    while (curr != nullptr) {
        std::cout << "Position " << position << " (Request #" << curr->requestId << "):\n  ";
        const Person* personPtr = &(curr->student);
        personPtr->displayInfo();
        std::cout << "\n----------------------------------------------------------------------\n";
        curr = curr->next;
        position++;
    }
    std::cout << "Total Booked Visits: " << count << "\n";
}
int linearSearchById(const PG list[], int count, int targetId) {
    for (int i = 0; i < count; i++) {
        if (list[i] == targetId) {
            return i;
        }
    }
    return -1;
}
int linearSearchByName(const PG list[], int count, const char* nameQuery, PG results[], int maxResults) {
    if (!nameQuery) return 0;
    int found = 0;
    size_t queryLen = strlen(nameQuery);
    for (int i = 0; i < count && found < maxResults; i++) {
        size_t nameLen = strlen(list[i].name);
        bool match = false;
        if (queryLen == 0) {
            match = true;
        } else if (nameLen >= queryLen) {
            for (size_t s = 0; s <= nameLen - queryLen; s++) {
                bool subMatch = true;
                for (size_t k = 0; k < queryLen; k++) {
                    if (tolower((unsigned char)list[i].name[s + k]) != tolower((unsigned char)nameQuery[k])) {
                        subMatch = false;
                        break;
                    }
                }
                if (subMatch) {
                    match = true;
                    break;
                }
            }
        }
        if (match) {
            results[found++] = list[i];
        }
    }
    return found;
}
void bubbleSortByRent(PG list[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (list[j] > list[j + 1]) {
                PG temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
}
int binarySearchByRent(const PG sortedList[], int count, double targetRent) {
    int low = 0;
    int high = count - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (sortedList[mid].rent == targetRent) {
            return mid;
        } else if (sortedList[mid].rent < targetRent) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}
void bubbleSortByScore(PG list[], double scores[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (scores[j] < scores[j + 1]) {
                double tempScore = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = tempScore;
                PG tempPG = list[j];
                list[j] = list[j + 1];
                list[j + 1] = tempPG;
            }
        }
    }
}
class UserPreference {
public:
    char preferredLocation[50];
    double maxBudget;
    char preferredGender[15];
    bool foodRequired;
    bool wifiRequired;
    bool acRequired;
    double maxDistance;
    double minRating;
    UserPreference();
    UserPreference(const char* loc, double budget, const char* gender,
                   bool food, bool wifi, bool ac, double dist, double rating);
    void displayPreferences() const;
};
UserPreference::UserPreference() {
    preferredLocation[0] = '\0';
    maxBudget = 0.0;
    preferredGender[0] = '\0';
    foodRequired = false;
    wifiRequired = false;
    acRequired = false;
    maxDistance = 0.0;
    minRating = 0.0;
}
UserPreference::UserPreference(const char* loc, double budget, const char* gender,
                               bool food, bool wifi, bool ac, double dist, double rating) {
    strncpy(preferredLocation, loc, sizeof(preferredLocation) - 1);
    preferredLocation[sizeof(preferredLocation) - 1] = '\0';
    maxBudget = budget;
    strncpy(preferredGender, gender, sizeof(preferredGender) - 1);
    preferredGender[sizeof(preferredGender) - 1] = '\0';
    foodRequired = food;
    wifiRequired = wifi;
    acRequired = ac;
    maxDistance = dist;
    minRating = rating;
}
void UserPreference::displayPreferences() const {
    std::cout << "\n----------------------------------------\n";
    std::cout << "        SEARCH PREFERENCES SUMMARY      \n";
    std::cout << "----------------------------------------\n";
    std::cout << "Preferred Location : " << (preferredLocation[0] == '\0' ? "Any" : preferredLocation) << "\n";
    std::cout << "Maximum Budget     : ";
    if (maxBudget > 0.0) std::cout << "Rs. " << std::fixed << std::setprecision(0) << maxBudget << "\n";
    else std::cout << "No limit\n";
    std::cout << "Preferred Gender   : " << (preferredGender[0] == '\0' ? "Any" : preferredGender) << "\n";
    std::cout << "Food Required      : " << (foodRequired ? "Yes" : "No") << "\n";
    std::cout << "Wi-Fi Required     : " << (wifiRequired ? "Yes" : "No") << "\n";
    std::cout << "AC Required        : " << (acRequired ? "Yes" : "No") << "\n";
    std::cout << "Maximum Distance   : ";
    if (maxDistance > 0.0) std::cout << std::fixed << std::setprecision(1) << maxDistance << " km\n";
    else std::cout << "No limit\n";
    std::cout << "Minimum Rating     : " << std::fixed << std::setprecision(1) << minRating << " / 5.0\n";
    std::cout << "----------------------------------------\n";
}
const int MAX_PGS = 100;
const char* const PG_DATA_FILE = "pg.txt";
class PGFinder {
private:
    PG dataset[MAX_PGS];
    int totalCount;
    PGLinkedList currentResultsList;
    SearchStack historyStack;
    VisitQueue requestQueue;
    int nextRequestId;
    bool stringContainsIgnoreCase(const char* fullText, const char* subQuery) const {
        if (!fullText || !subQuery) return false;
        if (subQuery[0] == '\0') return true;
        size_t fullLen = strlen(fullText);
        size_t subLen = strlen(subQuery);
        if (subLen > fullLen) return false;
        for (size_t i = 0; i <= fullLen - subLen; i++) {
            bool match = true;
            for (size_t j = 0; j < subLen; j++) {
                if (tolower((unsigned char)fullText[i + j]) != tolower((unsigned char)subQuery[j])) {
                    match = false;
                    break;
                }
            }
            if (match) return true;
        }
        return false;
    }
    bool stringEqualIgnoreCase(const char* s1, const char* s2) const {
        if (!s1 || !s2) return false;
        while (*s1 && *s2) {
            if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2)) return false;
            s1++;
            s2++;
        }
        return (*s1 == '\0' && *s2 == '\0');
    }
    bool isGenderCompatible(const PG& pg, const UserPreference& pref) const {
        if (pref.preferredGender[0] == '\0') return true;
        if (stringEqualIgnoreCase(pg.gender, "Unisex")) return true;
        return stringEqualIgnoreCase(pg.gender, pref.preferredGender);
    }
    bool meetsAllCriteria(const PG& pg, const UserPreference& pref) const {
        if (pref.maxBudget > 0.0 && pg.rent > pref.maxBudget) return false;
        if (pref.preferredLocation[0] != '\0' &&
            !stringContainsIgnoreCase(pg.location, pref.preferredLocation)) return false;
        if (pref.maxDistance > 0.0 && pg.distance > pref.maxDistance) return false;
        if (pref.foodRequired && !pg.foodAvailable) return false;
        if (pref.wifiRequired && !pg.wifiAvailable) return false;
        if (pref.acRequired && !pg.acAvailable) return false;
        if (pg.rating < pref.minRating) return false;
        return true;
    }
    double highestRent() const {
        double highest = 0.0;
        for (int i = 0; i < totalCount; i++) {
            if (dataset[i].rent > highest) highest = dataset[i].rent;
        }
        return highest;
    }
    double farthestDistance() const {
        double farthest = 0.0;
        for (int i = 0; i < totalCount; i++) {
            if (dataset[i].distance > farthest) farthest = dataset[i].distance;
        }
        return farthest;
    }
    int amenityCount(const PG& pg) const {
        return (pg.foodAvailable ? 1 : 0) + (pg.wifiAvailable ? 1 : 0) + (pg.acAvailable ? 1 : 0);
    }
    void showAvailableLocations() const {
        std::cout << "   Locations available in pg.txt: ";
        bool first = true;
        for (int i = 0; i < totalCount; i++) {
            bool seenBefore = false;
            for (int j = 0; j < i; j++) {
                if (stringEqualIgnoreCase(dataset[j].location, dataset[i].location)) {
                    seenBefore = true;
                    break;
                }
            }
            if (!seenBefore) {
                std::cout << (first ? "" : ", ") << dataset[i].location;
                first = false;
            }
        }
        std::cout << (first ? "none\n" : "\n");
    }
public:
    PGFinder() {
        totalCount = 0;
        nextRequestId = 1001;
    }
    void loadData() {
        totalCount = loadPGDataFromFile(dataset, MAX_PGS, PG_DATA_FILE);
    }
    void displayAll() const {
        std::cout << "\n========================================================================================\n";
        std::cout << "                           ALL AVAILABLE PGs (from pg.txt)                              \n";
        std::cout << "========================================================================================\n";
        displayAllPGRecords(dataset, totalCount);
    }
    void search(int targetId) {
        std::cout << "\n[Function Overload 1] Searching by PG ID: #" << targetId << "...\n";
        int idx = linearSearchById(dataset, totalCount, targetId);
        currentResultsList.clear();
        char details[100];
        snprintf(details, sizeof(details), "Overload(ID): #%d", targetId);
        if (idx != -1) {
            std::cout << ">> Match Found! Details:\n";
            dataset[idx].displayCard();
            currentResultsList.insertEnd(dataset[idx]);
            historyStack.push(SearchHistoryRecord("Search Overload [ID]", details, 1));
        } else {
            std::cout << ">> [Result] No PG found with ID #" << targetId << ".\n";
            historyStack.push(SearchHistoryRecord("Search Overload [ID]", details, 0));
        }
    }
    void search(const char* nameQuery) {
        std::cout << "\n[Function Overload 2] Searching by Name Keyword: \"" << nameQuery << "\"...\n";
        PG results[MAX_PGS];
        int found = linearSearchByName(dataset, totalCount, nameQuery, results, MAX_PGS);
        currentResultsList.clear();
        char details[100];
        snprintf(details, sizeof(details), "Overload(Name): \"%s\"", nameQuery);
        if (found > 0) {
            std::cout << ">> Found " << found << " matching PG(s):\n";
            for (int i = 0; i < found; i++) {
                results[i].displayCard();
                currentResultsList.insertEnd(results[i]);
            }
            historyStack.push(SearchHistoryRecord("Search Overload [Name]", details, found));
        } else {
            std::cout << ">> [Result] No PGs matched the name \"" << nameQuery << "\".\n";
            historyStack.push(SearchHistoryRecord("Search Overload [Name]", details, 0));
        }
    }
    void search(double minRent, double maxRent) {
        std::cout << "\n[Function Overload 3] Searching by Budget (Rent Range): Rs. "
                  << std::fixed << std::setprecision(0) << minRent << " to Rs. " << maxRent << "...\n";
        currentResultsList.clear();
        int found = 0;
        for (int i = 0; i < totalCount; i++) {
            if (dataset[i].rent >= minRent && dataset[i].rent <= maxRent) {
                dataset[i].displayCard();
                currentResultsList.insertEnd(dataset[i]);
                found++;
            }
        }
        char details[100];
        snprintf(details, sizeof(details), "Overload(RentRange): Rs.%.0f - Rs.%.0f", minRent, maxRent);
        if (found > 0) {
            std::cout << ">> Found " << found << " PG(s) within your budget range.\n";
            historyStack.push(SearchHistoryRecord("Search Overload [RentRange]", details, found));
        } else {
            std::cout << ">> [Result] No PGs found within this rent range.\n";
            historyStack.push(SearchHistoryRecord("Search Overload [RentRange]", details, 0));
        }
    }
    void searchByLocation(const char* locationQuery) {
        std::cout << "\n[Location Search] Searching PGs in: \"" << locationQuery << "\"...\n";
        currentResultsList.clear();
        int found = 0;
        for (int i = 0; i < totalCount; i++) {
            if (stringContainsIgnoreCase(dataset[i].location, locationQuery)) {
                dataset[i].displayCard();
                currentResultsList.insertEnd(dataset[i]);
                found++;
            }
        }
        char details[100];
        snprintf(details, sizeof(details), "Location: \"%s\"", locationQuery);
        if (found > 0) {
            std::cout << ">> Found " << found << " PG(s) in this location.\n";
        } else {
            std::cout << ">> [Result] No PGs found in \"" << locationQuery << "\".\n";
            showAvailableLocations();
        }
        historyStack.push(SearchHistoryRecord("Search [Location]", details, found));
    }
    void searchByExactRent(double targetRent) {
        std::cout << "\n[Binary Search for Rent: Rs. " << std::fixed << std::setprecision(0) << targetRent << "]\n";
        std::cout << "  Step 1: Sorting a copy of the list by rent using Bubble Sort (operator >)...\n";
        PG sortedCopy[MAX_PGS];
        for (int i = 0; i < totalCount; i++) sortedCopy[i] = dataset[i];
        bubbleSortByRent(sortedCopy, totalCount);
        std::cout << "  Step 2: Performing Binary Search (O(log N))...\n";
        int idx = binarySearchByRent(sortedCopy, totalCount, targetRent);
        currentResultsList.clear();
        char details[100];
        snprintf(details, sizeof(details), "Binary Search for Rent = Rs. %.0f", targetRent);
        if (idx != -1) {
            int first = idx;
            while (first > 0 && sortedCopy[first - 1].rent == targetRent) first--;
            int found = 0;
            for (int i = first; i < totalCount && sortedCopy[i].rent == targetRent; i++) {
                sortedCopy[i].displayCard();
                currentResultsList.insertEnd(sortedCopy[i]);
                found++;
            }
            std::cout << ">> Binary Search found " << found << " PG(s) with this exact rent.\n";
            historyStack.push(SearchHistoryRecord("Binary Search [Rent]", details, found));
        } else {
            std::cout << ">> [Result] No PG found with exact rent Rs. " << targetRent << ".\n";
            std::cout << "   Tip: use Search by Budget (rent range) to see nearby rents.\n";
            historyStack.push(SearchHistoryRecord("Binary Search [Rent]", details, 0));
        }
    }
    double calculateCompatibilityScore(const PG& pg, const UserPreference& pref) const {
        double budgetScore = 0.0;
        double locationScore = 0.0;
        double distanceScore = 0.0;
        double foodScore = 0.0;
        double wifiScore = 0.0;
        double acScore = 0.0;
        double genderScore = 0.0;
        double ratingScore = 0.0;
        if (pref.maxBudget <= 0.0) {
            budgetScore = 25.0;
        } else if (pg.rent <= pref.maxBudget) {
            double savingsRatio = (pref.maxBudget - pg.rent) / pref.maxBudget;
            budgetScore = 18.0 + (7.0 * savingsRatio);
        } else {
            double overshoot = (pg.rent - pref.maxBudget) / pref.maxBudget;
            if (overshoot < 0.15) {
                budgetScore = 12.0 * (1.0 - (overshoot / 0.15));
            } else {
                budgetScore = 0.0;
            }
        }
        if (pref.preferredLocation[0] == '\0' || stringContainsIgnoreCase(pg.location, pref.preferredLocation)) {
            locationScore = 20.0;
        } else {
            locationScore = 0.0;
        }
        if (pref.maxDistance <= 0.0) {
            distanceScore = 15.0;
        } else if (pg.distance <= pref.maxDistance) {
            distanceScore = 15.0 * (1.0 - (pg.distance / (pref.maxDistance + 0.1)));
        } else {
            distanceScore = 0.0;
        }
        if (pref.foodRequired) {
            foodScore = pg.foodAvailable ? 10.0 : 0.0;
        } else {
            foodScore = 10.0;
        }
        if (pref.wifiRequired) {
            wifiScore = pg.wifiAvailable ? 10.0 : 0.0;
        } else {
            wifiScore = 10.0;
        }
        if (pref.acRequired) {
            acScore = pg.acAvailable ? 5.0 : 0.0;
        } else {
            acScore = 5.0;
        }
        if (isGenderCompatible(pg, pref)) {
            genderScore = 5.0;
        } else {
            genderScore = 0.0;
        }
        if (pg.rating >= pref.minRating) {
            ratingScore = (pg.rating / 5.0) * 10.0;
        } else {
            ratingScore = (pg.rating / 5.0) * 5.0;
        }
        double total = budgetScore + locationScore + distanceScore +
                       foodScore + wifiScore + acScore + genderScore + ratingScore;
        if (total > 100.0) total = 100.0;
        if (total < 0.0) total = 0.0;
        return total;
    }
    void findAndRankBestPGs(const UserPreference& pref, bool strictOnly) {
        pref.displayPreferences();
        std::cout << "Filter Mode        : "
                  << (strictOnly ? "Only PGs that meet ALL requirements" : "All suitable PGs, best match first") << "\n";
        UserPreference scoringPref = pref;
        if (scoringPref.maxBudget <= 0.0) scoringPref.maxBudget = highestRent();
        if (scoringPref.maxDistance <= 0.0) scoringPref.maxDistance = farthestDistance();
        PG candidateList[MAX_PGS];
        double scores[MAX_PGS];
        int candidateCount = 0;
        for (int i = 0; i < totalCount; i++) {
            if (!isGenderCompatible(dataset[i], pref)) continue;
            if (strictOnly && !meetsAllCriteria(dataset[i], pref)) continue;
            candidateList[candidateCount] = dataset[i];
            scores[candidateCount] = calculateCompatibilityScore(dataset[i], scoringPref);
            candidateCount++;
        }
        bubbleSortByScore(candidateList, scores, candidateCount);
        currentResultsList.clear();
        for (int i = 0; i < candidateCount; i++) {
            currentResultsList.insertEnd(candidateList[i], scores[i]);
        }
        char budgetText[30];
        if (pref.maxBudget > 0.0) snprintf(budgetText, sizeof(budgetText), "Rs.%.0f", pref.maxBudget);
        else snprintf(budgetText, sizeof(budgetText), "No limit");
        char details[100];
        snprintf(details, sizeof(details), "Budget: %s | Loc: %s%s",
                 budgetText, (pref.preferredLocation[0] == '\0' ? "Any" : pref.preferredLocation),
                 (strictOnly ? " | Strict" : ""));
        historyStack.push(SearchHistoryRecord(strictOnly ? "Recommendation [Strict Filter]" : "Recommendation [Ranking]",
                                              details, candidateCount));
        if (candidateCount == 0) {
            std::cout << "\n>> [Result] No PG matches your requirements.\n";
            if (strictOnly) {
                std::cout << "   Tip: run it again without the strict filter to see the closest matches.\n";
            }
            return;
        }
        std::cout << "\n========================================\n";
        std::cout << "         RECOMMENDED PGs (RANKED)       \n";
        std::cout << "========================================\n\n";
        for (int i = 0; i < candidateCount; i++) {
            std::cout << "Rank: " << (i + 1) << "\n";
            std::cout << "PG ID         : " << candidateList[i].id << "\n";
            std::cout << "PG Name       : " << candidateList[i].name << "\n";
            std::cout << "Location      : " << candidateList[i].location << "\n";
            std::cout << "Rent          : Rs. " << std::fixed << std::setprecision(0) << candidateList[i].rent << "\n";
            std::cout << "Gender        : " << candidateList[i].gender << "\n";
            std::cout << "Food          : " << (candidateList[i].foodAvailable ? "Yes" : "No") << "\n";
            std::cout << "Wi-Fi         : " << (candidateList[i].wifiAvailable ? "Yes" : "No") << "\n";
            std::cout << "AC            : " << (candidateList[i].acAvailable ? "Yes" : "No") << "\n";
            std::cout << "Distance      : " << std::setprecision(1) << candidateList[i].distance << " km\n";
            std::cout << "Rating        : " << candidateList[i].rating << "/5\n";
            std::cout << "Match Score   : " << std::fixed << std::setprecision(1) << scores[i] << "/100\n";
            std::cout << "----------------------------------------\n";
        }
        std::cout << "Ranked and displayed " << candidateCount << " PG(s).\n";
        std::cout << "[Notice] Results are saved in the Singly Linked List (menu option 9).\n";
    }
    void comparePGs(int firstId, int secondId) {
        if (firstId == secondId) {
            std::cout << "\n[Notice] Please choose two different PG IDs to compare.\n";
            return;
        }
        int a = linearSearchById(dataset, totalCount, firstId);
        int b = linearSearchById(dataset, totalCount, secondId);
        if (a == -1 || b == -1) {
            std::cout << "\n[Error] PG ID #" << (a == -1 ? firstId : secondId) << " does not exist.\n";
            return;
        }
        const PG& p1 = dataset[a];
        const PG& p2 = dataset[b];
        std::cout << "\n==================== COMPARE PGs ====================\n";
        std::cout << "PG 1:\n";
        p1.displayCard();
        std::cout << "PG 2:\n";
        p2.displayCard();
        int p1Points = 0;
        int p2Points = 0;
        std::cout << "\n------------------ COMPARISON SUMMARY ------------------\n";
        std::cout << "Lower Rent        : ";
        if (p1.rent < p2.rent) {
            std::cout << p1.name << " (Rs. " << std::fixed << std::setprecision(0) << (p2.rent - p1.rent) << " cheaper)\n";
            p1Points++;
        } else if (p2.rent < p1.rent) {
            std::cout << p2.name << " (Rs. " << std::fixed << std::setprecision(0) << (p1.rent - p2.rent) << " cheaper)\n";
            p2Points++;
        } else {
            std::cout << "Same rent\n";
        }
        std::cout << "Closer to College : ";
        if (p1.distance < p2.distance) {
            std::cout << p1.name << " (" << std::fixed << std::setprecision(1) << (p2.distance - p1.distance) << " km closer)\n";
            p1Points++;
        } else if (p2.distance < p1.distance) {
            std::cout << p2.name << " (" << std::fixed << std::setprecision(1) << (p1.distance - p2.distance) << " km closer)\n";
            p2Points++;
        } else {
            std::cout << "Same distance\n";
        }
        std::cout << "Better Rating     : ";
        if (p1.rating > p2.rating) {
            std::cout << p1.name << "\n";
            p1Points++;
        } else if (p2.rating > p1.rating) {
            std::cout << p2.name << "\n";
            p2Points++;
        } else {
            std::cout << "Same rating\n";
        }
        int amenities1 = amenityCount(p1);
        int amenities2 = amenityCount(p2);
        std::cout << "More Amenities    : ";
        if (amenities1 > amenities2) {
            std::cout << p1.name << " (" << amenities1 << " of 3 vs " << amenities2 << " of 3)\n";
            p1Points++;
        } else if (amenities2 > amenities1) {
            std::cout << p2.name << " (" << amenities2 << " of 3 vs " << amenities1 << " of 3)\n";
            p2Points++;
        } else {
            std::cout << "Same (" << amenities1 << " of 3 each)\n";
        }
        std::cout << "--------------------------------------------------------\n";
        if (p1Points > p2Points) {
            std::cout << "Overall: " << p1.name << " is better on " << p1Points << " of 4 points.\n";
        } else if (p2Points > p1Points) {
            std::cout << "Overall: " << p2.name << " is better on " << p2Points << " of 4 points.\n";
        } else {
            std::cout << "Overall: Both PGs are equal (" << p1Points << " - " << p2Points << ").\n";
        }
        if (!stringEqualIgnoreCase(p1.gender, p2.gender)) {
            std::cout << "Note: these PGs are for different genders (" << p1.gender << " / " << p2.gender << ").\n";
        }
    }
    void viewSearchHistory() const {
        historyStack.displayHistory();
    }
    void undoLastSearch() {
        SearchHistoryRecord popped;
        if (historyStack.pop(popped)) {
            std::cout << "\n[Undo Success - LIFO] Removed the most recent search:\n";
            std::cout << "  Title    : " << popped.searchTitle << "\n";
            std::cout << "  Criteria : " << popped.criteriaDetails << "\n";
            std::cout << "  Matches  : " << popped.resultCount << " record(s)\n";
            currentResultsList.clear();
            std::cout << "  Current Linked List results have been cleared.\n";
        } else {
            std::cout << "\n[Stack Error] Cannot Undo: search history is empty.\n";
        }
    }
    void addVisitRequest(const char* studentName, const char* contact, const char* college, int pgId) {
        int idx = linearSearchById(dataset, totalCount, pgId);
        if (idx == -1) {
            std::cout << "[Error] Cannot book visit: PG ID #" << pgId << " does not exist.\n";
            return;
        }
        StudentUser student(studentName, contact, college, pgId);
        requestQueue.enqueue(student, nextRequestId);
        std::cout << ">> Visit request #" << nextRequestId << " booked for \"" << dataset[idx].name
                  << "\". Position in your visit queue: " << requestQueue.getCount() << ".\n";
        nextRequestId++;
    }
    void viewBookedVisits() const {
        requestQueue.displayQueue();
        StudentUser nextStudent;
        int reqId = 0;
        if (requestQueue.peek(nextStudent, reqId)) {
            int idx = linearSearchById(dataset, totalCount, nextStudent.getTargetPGId());
            std::cout << "Next visit (front of queue): Request #" << reqId << " -> "
                      << (idx != -1 ? dataset[idx].name : "Unknown PG") << "\n";
        }
    }
    void completeNextVisit() {
        StudentUser visitedStudent;
        int reqId = 0;
        if (requestQueue.dequeue(visitedStudent, reqId)) {
            int idx = linearSearchById(dataset, totalCount, visitedStudent.getTargetPGId());
            std::cout << "\n================ VISIT COMPLETED (QUEUE - DEQUEUE) ================\n";
            std::cout << "Request #" << reqId << " for \""
                      << (idx != -1 ? dataset[idx].name : "Unknown PG") << "\" is marked as done.\n  ";
            const Person* personPtr = &visitedStudent;
            personPtr->displayInfo();
            std::cout << "\nVisits still pending: " << requestQueue.getCount() << "\n";
            std::cout << "===================================================================\n";
        } else {
            std::cout << "\n[Queue Empty] You have no pending PG visits.\n";
        }
    }
    void displayLinkedListResults() const {
        currentResultsList.displayList();
    }
    void displayLinkedListResults(int topN) const {
        currentResultsList.displayList(topN);
    }
};
static PGFinder systemEngine;
void engineLoadData() {
    systemEngine.loadData();
}
void engineDisplayAll() {
    systemEngine.displayAll();
}
void engineSearchById(int targetId) {
    systemEngine.search(targetId);
}
void engineSearchByName(const char* nameQuery) {
    systemEngine.search(nameQuery);
}
void engineSearchByLocation(const char* locationQuery) {
    systemEngine.searchByLocation(locationQuery);
}
void engineSearchByRentRange(double minRent, double maxRent) {
    systemEngine.search(minRent, maxRent);
}
void engineSearchByRent(double rent) {
    systemEngine.searchByExactRent(rent);
}
void engineFindAndRank(const UserPreference& pref, bool strictOnly) {
    systemEngine.findAndRankBestPGs(pref, strictOnly);
}
void engineComparePGs(int firstId, int secondId) {
    systemEngine.comparePGs(firstId, secondId);
}
void engineViewHistory() {
    systemEngine.viewSearchHistory();
}
void engineUndoSearch() {
    systemEngine.undoLastSearch();
}
void engineAddVisitRequest(const char* name, const char* contact, const char* college, int pgId) {
    systemEngine.addVisitRequest(name, contact, college, pgId);
}
void engineViewBookedVisits() {
    systemEngine.viewBookedVisits();
}
void engineCompleteNextVisit() {
    systemEngine.completeNextVisit();
}
void engineDisplayLinkedList() {
    systemEngine.displayLinkedListResults();
}
void engineDisplayLinkedListTopN(int topN) {
    systemEngine.displayLinkedListResults(topN);
}
const int EXIT_CHOICE = 14;
const int MAX_ID = 999999999;
const double MAX_RENT = 10000000.0;
static bool inputEnded = false;
static std::string readLine(const char* prompt) {
    std::cout << prompt;
    std::string line;
    if (!std::getline(std::cin, line)) {
        inputEnded = true;
        std::cout << "\n";
        return "";
    }
    size_t start = 0;
    size_t end = line.length();
    while (start < end && (line[start] == ' ' || line[start] == '\t' || line[start] == '\r')) start++;
    while (end > start && (line[end - 1] == ' ' || line[end - 1] == '\t' || line[end - 1] == '\r')) end--;
    return line.substr(start, end - start);
}
int getIntInput(const char* prompt, int minVal, int maxVal) {
    while (true) {
        std::string line = readLine(prompt);
        if (inputEnded) return minVal;
        if (line.empty()) continue;
        if (isWholeNumber(line) && line.length() <= 9) {
            int value = std::stoi(line);
            if (value >= minVal && value <= maxVal) return value;
        }
        std::cout << "[Input Error] Please enter a whole number from " << minVal << " to " << maxVal << ".\n";
    }
}
double getDoubleInput(const char* prompt, double minVal, double maxVal) {
    while (true) {
        std::string line = readLine(prompt);
        if (inputEnded) return minVal;
        if (line.empty()) continue;
        if (isDecimalNumber(line) && line.length() <= 12) {
            double value = std::stod(line);
            if (value >= minVal && value <= maxVal) return value;
        }
        std::cout << "[Input Error] Please enter a number from " << (long)minVal << " to " << (long)maxVal
                  << " (digits only, e.g. 7500 or 2.5).\n";
    }
}
void getStringInput(const char* prompt, char* outputBuffer, int bufferSize, bool required) {
    while (true) {
        std::string line = readLine(prompt);
        if (inputEnded) {
            outputBuffer[0] = '\0';
            return;
        }
        if (required && line.empty()) {
            std::cout << "[Input Error] This field cannot be empty.\n";
            continue;
        }
        strncpy(outputBuffer, line.c_str(), bufferSize - 1);
        outputBuffer[bufferSize - 1] = '\0';
        return;
    }
}
bool getYesNoInput(const char* prompt) {
    while (true) {
        std::string line = readLine(prompt);
        if (inputEnded) return false;
        if (!line.empty()) {
            char ch = (char)std::tolower(static_cast<unsigned char>(line[0]));
            if (ch == 'y') return true;
            if (ch == 'n') return false;
        }
        std::cout << "[Input Error] Please type 'Y' for Yes or 'N' for No.\n";
    }
}
void getPhoneInput(const char* prompt, char* outputBuffer, int bufferSize) {
    while (true) {
        std::string line = readLine(prompt);
        if (inputEnded) {
            outputBuffer[0] = '\0';
            return;
        }
        if (line.length() == 10 && isWholeNumber(line)) {
            strncpy(outputBuffer, line.c_str(), bufferSize - 1);
            outputBuffer[bufferSize - 1] = '\0';
            return;
        }
        std::cout << "[Input Error] Please enter a 10-digit mobile number (digits only).\n";
    }
}
void handleSearchById() {
    int id = getIntInput("Enter PG ID to search (e.g. 101): ", 1, MAX_ID);
    if (inputEnded) return;
    engineSearchById(id);
}
void handleSearchByName() {
    char nameQuery[50];
    getStringInput("Enter PG Name or Keyword (e.g. Valley, Haven, Royal): ", nameQuery, sizeof(nameQuery), true);
    if (inputEnded) return;
    engineSearchByName(nameQuery);
}
void handleSearchByLocation() {
    char location[50];
    getStringInput("Enter Location / Area (e.g. ISBT, Clement Town, Subhash Nagar, Mohabewala): ", location, sizeof(location), true);
    if (inputEnded) return;
    engineSearchByLocation(location);
}
void handleSearchByRentRange() {
    double minRent = getDoubleInput("Enter Minimum Monthly Rent in Rs.: ", 0.0, MAX_RENT);
    double maxRent = getDoubleInput("Enter Maximum Monthly Rent in Rs.: ", 0.0, MAX_RENT);
    if (inputEnded) return;
    if (maxRent < minRent) {
        std::cout << "[Notice] Maximum rent was lower than minimum rent. Swapping the values.\n";
        double temp = minRent;
        minRent = maxRent;
        maxRent = temp;
    }
    engineSearchByRentRange(minRent, maxRent);
}
void handleSearchByRent() {
    double rent = getDoubleInput("Enter Exact Monthly Rent to find with Binary Search (Rs.): ", 1.0, MAX_RENT);
    if (inputEnded) return;
    engineSearchByRent(rent);
}
void handleFindAndRankBestPGs() {
    std::cout << "\n========================================\n";
    std::cout << "   ENTER YOUR PREFERENCES FOR RANKING   \n";
    std::cout << "========================================\n";
    char location[50];
    getStringInput("Preferred Location (press Enter for Any): ", location, sizeof(location), false);
    double budget = getDoubleInput("Maximum Monthly Budget in Rs. (0 = no limit): ", 0.0, MAX_RENT);
    std::cout << "Preferred PG Type:\n  1. Boys\n  2. Girls\n  3. Unisex (co-ed) only\n  4. Any\n";
    int genderChoice = getIntInput("Choose PG Type (1-4): ", 1, 4);
    const char* gender = "";
    if (genderChoice == 1) gender = "Boys";
    else if (genderChoice == 2) gender = "Girls";
    else if (genderChoice == 3) gender = "Unisex";
    bool food = getYesNoInput("Food Required? (Y/N): ");
    bool wifi = getYesNoInput("Wi-Fi Required? (Y/N): ");
    bool ac = getYesNoInput("AC Required? (Y/N): ");
    double dist = getDoubleInput("Maximum Distance from College in km (0 = no limit): ", 0.0, 100.0);
    double rating = getDoubleInput("Minimum Acceptable Star Rating (0 to 5): ", 0.0, 5.0);
    bool strictOnly = getYesNoInput("Show ONLY PGs that meet ALL of the above? (Y = strict filter, N = rank all): ");
    if (inputEnded) return;
    UserPreference pref(location, budget, gender, food, wifi, ac, dist, rating);
    engineFindAndRank(pref, strictOnly);
}
void handleComparePGs() {
    std::cout << "\n[Tip] Use option 1 to see the PG IDs.\n";
    int firstId = getIntInput("Enter the first PG ID: ", 1, MAX_ID);
    int secondId = getIntInput("Enter the second PG ID: ", 1, MAX_ID);
    if (inputEnded) return;
    engineComparePGs(firstId, secondId);
}
void handleAddVisitRequest() {
    std::cout << "\n========================================\n";
    std::cout << "          BOOK A PG VISIT               \n";
    std::cout << "========================================\n";
    char name[50];
    getStringInput("Enter Your Full Name: ", name, sizeof(name), true);
    char phone[20];
    getPhoneInput("Enter Your Mobile Number (10 digits): ", phone, sizeof(phone));
    char college[50];
    getStringInput("Enter Your College / University Name: ", college, sizeof(college), true);
    int pgId = getIntInput("Enter PG ID you want to visit (e.g. 101): ", 1, MAX_ID);
    if (inputEnded) return;
    engineAddVisitRequest(name, phone, college, pgId);
}
void handleBookedVisits() {
    std::cout << "\n[My Booked Visits - Queue (FIFO)]\n";
    std::cout << "1. View all my booked visits\n";
    std::cout << "2. Mark the next visit as done (Dequeue)\n";
    int opt = getIntInput("Select option (1-2): ", 1, 2);
    if (inputEnded) return;
    if (opt == 2) {
        engineCompleteNextVisit();
    } else {
        engineViewBookedVisits();
    }
}
void handleDisplayLinkedList() {
    std::cout << "\n[Display Linked List - Function Overload Options]:\n";
    std::cout << "1. Display All Results in Linked List\n";
    std::cout << "2. Display Top N Results (Overloaded)\n";
    int opt = getIntInput("Select display option (1-2): ", 1, 2);
    if (inputEnded) return;
    if (opt == 2) {
        int n = getIntInput("Enter number of top results to view (e.g. 3): ", 1, 100);
        if (inputEnded) return;
        engineDisplayLinkedListTopN(n);
    } else {
        engineDisplayLinkedList();
    }
}
int main() {
    std::cout << "Starting Smart PG Finder...\n";
    engineLoadData();
    int choice = 0;
    while (choice != EXIT_CHOICE) {
        std::cout << "\n=======================================================\n";
        std::cout << "            SMART PG FINDER - STUDENT PORTAL           \n";
        std::cout << "        Find the right PG near your college            \n";
        std::cout << "=======================================================\n";
        std::cout << " 1. View All Available PGs\n";
        std::cout << " 2. Search PG by ID               [Overload 1]\n";
        std::cout << " 3. Search PG by Name             [Overload 2]\n";
        std::cout << " 4. Search PG by Location\n";
        std::cout << " 5. Search PG by Budget (Range)   [Overload 3]\n";
        std::cout << " 6. Search PG by Exact Rent       [Binary Search]\n";
        std::cout << " 7. Get Recommended PGs           [Multi-Criteria Score /100]\n";
        std::cout << " 8. Compare Two PGs\n";
        std::cout << " 9. View Current Results          [Linked List]\n";
        std::cout << "10. View Search History           [Stack - LIFO]\n";
        std::cout << "11. Undo Last Search              [Stack Pop]\n";
        std::cout << "12. Book a PG Visit               [Queue - Enqueue]\n";
        std::cout << "13. My Booked Visits              [Queue - FIFO]\n";
        std::cout << "14. Exit\n";
        std::cout << "=======================================================\n";
        choice = getIntInput("Enter your choice (1-14): ", 1, EXIT_CHOICE);
        if (inputEnded) break;
        switch (choice) {
            case 1:
                engineDisplayAll();
                break;
            case 2:
                handleSearchById();
                break;
            case 3:
                handleSearchByName();
                break;
            case 4:
                handleSearchByLocation();
                break;
            case 5:
                handleSearchByRentRange();
                break;
            case 6:
                handleSearchByRent();
                break;
            case 7:
                handleFindAndRankBestPGs();
                break;
            case 8:
                handleComparePGs();
                break;
            case 9:
                handleDisplayLinkedList();
                break;
            case 10:
                engineViewHistory();
                break;
            case 11:
                engineUndoSearch();
                break;
            case 12:
                handleAddVisitRequest();
                break;
            case 13:
                handleBookedVisits();
                break;
            case EXIT_CHOICE:
                break;
            default:
                std::cout << "\n[Error] Invalid choice. Please select a number from 1 to 14.\n";
                break;
        }
        if (inputEnded) break;
    }
    std::cout << "\nThank you for using Smart PG Finder! All the best for your new PG.\n";
    return 0;
}