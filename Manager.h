#pragma once

#include <string>
#include <vector>

using namespace std;

template <typename T>
class Manager {
protected:
    string fileName;
    vector<T> items;

public:
    explicit Manager(const string& fileName = "") : fileName(fileName) {}
    virtual ~Manager() = default;

    const string& getFileName() const { return fileName; }
    const vector<T>& getItems() const { return items; }
    size_t size() const { return items.size(); }

    virtual bool load() = 0;
    virtual bool save() const = 0;
    virtual const T* findById(const string& id) const = 0;
};
