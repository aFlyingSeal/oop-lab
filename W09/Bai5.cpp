#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Component{
private:
    string name;
public:
    Component(const string& name){
        this->name = name;
    }

    virtual void print(ostream& out, int depth) = 0;
    virtual double getSize() = 0;
    virtual void countItem(int& dirCount, int& fileCount) = 0;
    virtual Component* findFolder(const string& name) = 0;

    string getName(){ return name; }

    virtual ~Component(){}
};

class File: public Component{
private:
    double size;
public:
    File(const string& name, double size): Component(name){
        this->size = size;
    }

    void print(ostream& out, int depth){
        for (int i = 1; i <= depth; i++){
            out << "\t";
        }
        out << Component::getName() << " (" << size << " B)\n";
    }

    double getSize(){
        return size;
    }

    void countItem(int& dirCount, int& fileCount){
        fileCount++;
    }

    Component* findFolder(const string& name){
        return nullptr;
    }
};

class Folder: public Component{
private:
    vector<Component*> itemList;
public:
    Folder(const string& name): Component(name){}

    void addItem(Component* item){
        itemList.push_back(item);
    }

    void print(ostream& out, int depth){
        for (int i = 1; i <= depth; i++){
            out << "\t";
        }
        out << "[" << Component::getName() << "]\n";
        for (int i = 0; i < itemList.size(); i++){
            itemList[i]->print(out, depth + 1);
        }
    }

    double getSize(){
        double totalSize = 0;
        for (int i = 0; i < itemList.size(); i++){
            totalSize += itemList[i]->getSize();
        }
        return totalSize;
    }

    void countItem(int& dirCount, int& fileCount){
        dirCount++;
        for (int i = 0; i < itemList.size(); i++){
            itemList[i]->countItem(dirCount, fileCount);
        }
    }

    Component* findFolder(const string& name){
        if (Component::getName() == name){
            return this;
        }
        for (int i = 0; i < itemList.size(); i++){
            Component* found = itemList[i]->findFolder(name);
            if (found != nullptr)
                return found;
        }
        return nullptr;
    }
};

class Disk{
private:
    string name;

    vector<Component*> itemList;
public:
    Disk(const string& name){
        this->name = name;
    }

    void addItem(Component* item){
        itemList.push_back(item);
    }

    void print(ostream& out) const{
        out << "[" << name << "]\n";
        for (int i = 0; i < itemList.size(); i++){
            itemList[i]->print(out, 1);
        }
        out << endl;
    }

    void findFolder(ostream& out, const string& name){
        for (int i = 0; i < itemList.size(); i++){
            Component* found = itemList[i]->findFolder(name);
            if (found != nullptr){
                out << "\"" << name << "\" is found\n";

                found->print(out, 0);

                int dirCount = -1, fileCount = 0;
                found->countItem(dirCount, fileCount);

                out << "Folder count: " << dirCount << endl
                    << "File count: " << fileCount << endl
                    << "Total size: " << found->getSize() << endl << endl;

                return;
            }
        }
        cout << "Folder \"" << name << "\" not found\n";
    }

    friend ostream& operator<<(ostream& out, const Disk& disk){
        disk.print(out);
        return out;
    }
};

int main(){
    Disk* disk = new Disk("C:");

    Component* bt = new Folder("Bai tap");
    ((Folder*)bt)->addItem(new File("BT1.doc", 123.456));

    Component* btC = new Folder("Bai tap C");
    ((Folder*)btC)->addItem(new File("BT2.cpp", 1.280));
    ((Folder*)bt)->addItem(btC);
    ((Folder*)bt)->addItem(new File("BT2.xls", 23.456));

    Component* lt = new Folder("Ly thuyet");
    ((Folder*)lt)->addItem(new File("Ch1.ppt", 34.567));

    disk->addItem(bt);
    disk->addItem(lt);

    cout << *disk;

    disk->findFolder(cout, "Bai tap C");
    disk->findFolder(cout, "Bai tap");
    disk->findFolder(cout, "BT3.cpp");
}