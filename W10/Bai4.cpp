#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<stdexcept>

using namespace std;

class MyException: public runtime_error{
private:
    string errorDescription;
    int errorCode;
public:
    MyException(int errCode, const string& errDesc): runtime_error(BuildErrorMessage(errCode, errDesc)){
        errorDescription = errDesc;
        errorCode = errCode;
    }
    string& GetErrorDescription(){
        return errorDescription;
    }
    int GetErrorCode(){
        return errorCode;
    }
private:
    static const string BuildErrorMessage(int errCode, const string& errDesc){
        string message = "";
        message = message + "Error code: " + to_string(errCode);
        message = message + " - Description: " + errDesc;
        return message;
    }
};

class CItem{
protected:
    string name;
    bool isHidden;
public:
    CItem(const string& name){
        if (name == ""){
            throw MyException(1, "FIle name must not be empty");
        }
        this->name = name;
        isHidden = false;
    }

    virtual int GetSize() = 0;

    virtual void Print(bool printHidden, int depth = 0) = 0;

    virtual void SetHidden(bool isHidden, bool applyToChildren){
        this->isHidden = isHidden;
    }

    string GetName(){ return name; }
};

class CFile: public CItem{
private:
    int size;
public:
    CFile(const string& name, int size): CItem(name){
        if (size <= 0){
            throw MyException(2, "File size must not be negative");
        }
        this->size = size;
    }

    int GetSize(){
        return size;
    }

    void Print(bool printHidden, int depth){
        if (printHidden == false && isHidden){
            return;
        }
        for (int i = 1; i <= depth; i++)
            cout << "\t";
        cout << name << " [" << GetSize() << "] (hidden: " << isHidden << ")\n"; 
    }

    void SetHidden(bool isHidden, bool applyToChildren){
        CItem::SetHidden(isHidden, applyToChildren);
    }
};

class CFolder: public CItem{
private:
    vector<CItem*> items;
public:
    CFolder(const string& name): CItem(name){}

    int GetSize(){
        int totalSize = 0;
        for (CItem* item: items){
            totalSize += item->GetSize();
        }
        return totalSize;
    }

    void Print(bool printHidden, int depth = 0){
        if (printHidden == false && isHidden){
            return;
        }
        for (int i = 0; i < depth; i++)
            cout << "\t";
        cout << name << " [" << GetSize() << "] (hidden: " << isHidden << ")\n";
        for (CItem* item: items){
            item->Print(printHidden, depth + 1);
        }
    }

    void Add(CItem* newItem){
        if (newItem == nullptr){
            throw MyException(3, "Argument must not be null");
        }
        for (CItem* item: items){
            if (item->GetName() == newItem->GetName()){
                throw MyException(4, "Duplicated file name");
            }
        }
        items.push_back(newItem);
    }

    CItem* RemoveByName(const string& target){
        for (int i = 0; i < items.size(); i++){
            if (items[i]->GetName() == target){
                CItem* toRemove = items[i];
                items.erase(items.begin() + i);
                return toRemove;
            }
        }
        for (CItem* item: items){
            CFolder* folder = dynamic_cast<CFolder*>(item);
            if (folder != nullptr){
                CItem* toRemove = folder->RemoveByName(target);
                if (toRemove != nullptr){
                    return toRemove;
                }
            }
        }
        return nullptr;
    }

    CItem* FindByName(const string& target){
        for (int i = 0; i < items.size(); i++){
            if (items[i]->GetName() == target){
                return items[i];
            }
        }
        for (CItem* item: items){
            CFolder* folder = dynamic_cast<CFolder*>(item);
            if (folder != nullptr){
                CItem* toFind = folder->FindByName(target);
                if (toFind != nullptr){
                    return toFind;
                }
            }
        }
        return nullptr;
    }

    void SetHidden(bool isHidden, bool applyToChildren){
        CItem::SetHidden(isHidden, applyToChildren);
        if (applyToChildren){
            for (CItem* item: items){
                item->SetHidden(isHidden, applyToChildren);
            }
        }
    }
};

int main(){
    try{
        CFolder C("C");
        CFolder System("System");
        CFolder Windows("Windows");
        CFile a_txt("a.txt", 123);
        CFile b_doc("b.doc", 456);

        System.Add(&a_txt);
        Windows.Add(&b_doc);
        C.Add(&System);
        C.Add(&Windows);

        cout << "Content of folder C ->" << endl;
        bool isPrintHiddenItems = false;
        C.Print(isPrintHiddenItems);

        CItem* p = C.RemoveByName("System");
        cout << "Content of folder C after removing folder System ->" << endl;
        C.Print(false);

        p = C.FindByName("b.doc");
        if (p != nullptr){
            cout << "b.doc is found in folder C" << endl;
        }
        else{
            cout << "b.doc is not found" << endl;
        }
        p = C.FindByName("a.txt");
        if (p != nullptr){
            cout << "a.txt is found in folder C" << endl;
        }
        else{
            cout << "a.txt is not found" << endl;
        }

        p = C.FindByName("Windows");
        bool isHidden;
        bool isAlsoApplyToChildren;
        if (p != nullptr){
            cout << "Folder Windows is in folder C. Content of folder Windows ->" << endl;

            isHidden = true; isAlsoApplyToChildren = false;
            p->SetHidden(isHidden, isAlsoApplyToChildren);
            p->Print(false);

            isHidden = true; isAlsoApplyToChildren = true;
            p->SetHidden(isHidden, isAlsoApplyToChildren);
            p->Print(false);
        }
        else{
            cout << "Folder Windows is not found" << endl;
        }
    }
    catch (const MyException& e){
        cout << "Custom error: " << e.what() << endl;
    }
    catch (const exception& e){
        cout << "Common error: " << e.what() << endl;
    }

    return 0;
}