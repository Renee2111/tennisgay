#ifndef YARDSTATS_H
#define YARDSTATS_H

#include <string>
#include <map>

class YardStats {
private:
    std::string dataDir;

public:
    YardStats(const std::string &dir = "./data");

    // Thống kê doanh thu theo từng tháng (ví dụ: "2023-10" -> tổng tiền)
    std::map<std::string, double> getRevenueByMonth();

    // Thống kê doanh thu theo từng sân (ví dụ: "Y01" -> tổng tiền)
    std::map<std::string, double> getRevenueByYard();

    // Thống kê số lần sân được đặt (ví dụ: "Y01" -> số lượt)
    std::map<std::string, int> getUsageCountByYard();

    // Lấy tổng doanh thu tất cả các hóa đơn
    double getTotalRevenue();
};

#endif // YARDSTATS_H