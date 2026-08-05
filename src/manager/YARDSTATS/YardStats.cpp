#include "YardStats.h"
#include "../../util/FILEHANDLER/FileHandler.h"
#include "../../model/INVOICE/Invoice.h"
#include <iostream>

YardStats::YardStats(const std::string &dir) {
    dataDir = dir;
    if (!dataDir.empty() && dataDir.back() != '/' && dataDir.back() != '\\') {
        dataDir += "/";
    }
}

// 1. Thống kê doanh thu theo tháng
std::map<std::string, double> YardStats::getRevenueByMonth() {
    std::map<std::string, double> revenueMap;
    std::string *lines = nullptr;
    
    int count = FileHandler::readFile(dataDir + "invoices.csv", lines);
    for (int i = 0; i < count; i++) {
        Invoice inv;
        inv.fromCSV(lines[i]);
        
        // Giả sử dateFrom có dạng "YYYY-MM-DD" -> Lấy 7 ký tự đầu làm chuỗi "YYYY-MM"
        std::string month = inv.getDateFrom();
        if (month.length() >= 7) {
            month = month.substr(0, 7);
        } else {
            month = "Unknown";
        }
        
        // Sử dụng inv.getTotal() chuẩn theo Invoice.cpp của bạn
        revenueMap[month] += inv.getTotal(); 
    }
    
    delete[] lines;
    return revenueMap;
}

// 2. Thống kê doanh thu theo từng sân
std::map<std::string, double> YardStats::getRevenueByYard() {
    std::map<std::string, double> revenueMap;
    std::string *lines = nullptr;

    int count = FileHandler::readFile(dataDir + "invoices.csv", lines);
    for (int i = 0; i < count; i++) {
        Invoice inv;
        inv.fromCSV(lines[i]);
        
        // Sử dụng inv.getTotal() chuẩn theo Invoice.cpp của bạn
        revenueMap[inv.getYardId()] += inv.getTotal(); 
    }

    delete[] lines;
    return revenueMap;
}

// 3. Thống kê số lần đặt theo từng sân
std::map<std::string, int> YardStats::getUsageCountByYard() {
    std::map<std::string, int> usageMap;
    std::string *lines = nullptr;

    int count = FileHandler::readFile(dataDir + "invoices.csv", lines);
    for (int i = 0; i < count; i++) {
        Invoice inv;
        inv.fromCSV(lines[i]);
        
        usageMap[inv.getYardId()]++;
    }

    delete[] lines;
    return usageMap;
}

// 4. Tính tổng doanh thu toàn bộ
double YardStats::getTotalRevenue() {
    double total = 0.0;
    std::string *lines = nullptr;

    int count = FileHandler::readFile(dataDir + "invoices.csv", lines);
    for (int i = 0; i < count; i++) {
        Invoice inv;
        inv.fromCSV(lines[i]);
        
        // Sử dụng inv.getTotal() chuẩn theo Invoice.cpp của bạn
        total += inv.getTotal(); 
    }

    delete[] lines;
    return total;
}   