#pragma once
#include <string>
#include <iostream>

using namespace std;

// LỚP CHA: Ticket (Trừu tượng)
class Ticket {
protected:
    string ticketId;
    double price;
public:
    Ticket(string id, double p) : ticketId(id), price(p) {}
    virtual ~Ticket() = default;
    
    double getPrice() const { return price; }
    virtual void displayTicket() const = 0; // Hàm ảo thuần túy bắt buộc lớp con phải viết
};

// LỚP CON 1: Vé Thường (Kế thừa Ticket)
class StandardTicket : public Ticket {
public:
    StandardTicket(string id, double p) : Ticket(id, p) {}
    
    void displayTicket() const override {
        cout << "[VE THUONG] Ma ve: " << ticketId << " | Gia: " << price << " VND" << endl;
    }
};

// LỚP CON 2: Vé VIP (Kế thừa Ticket)
class VIPTicket : public Ticket {
private:
    string extraPerks; // Đặc quyền thêm
public:
    // Khởi tạo vé VIP: Giá cơ bản tự động nhân 1.5 lần và có kèm bắp nước
    VIPTicket(string id, double p, string perks = "Combo Bap Nuoc Mien Phi") 
        : Ticket(id, p * 1.5), extraPerks(perks) {}
        
    void displayTicket() const override {
        cout << "[VE VIP] Ma ve: " << ticketId << " | Gia: " << price << " VND" << endl;
        cout << ">> Dac quyen: " << extraPerks << endl;
    }
};