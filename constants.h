#pragma once

namespace InventoryConstants {

// Database
constexpr const char* DEFAULT_DATABASE_NAME = "snipeit_db";

// Zone configuration: maps array index to DB value, widget name, and checkout location ID
struct ZoneConfig {
    int index;
    const char* dbValue;
    const char* widgetName;
    int locationId;
};

constexpr int ZONE_COUNT = 11;

constexpr ZoneConfig ZONES[ZONE_COUNT] = {
    { 0, "0",   "zone0",  4  },
    { 1, "1",   "zone1",  5  },
    { 2, "2",   "zone2",  6  },
    { 3, "3",   "zone3",  7  },
    { 4, "4",   "zone4",  8  },
    { 5, "5",   "zone5",  9  },
    { 6, "6",   "zone6",  10 },
    { 7, "7",   "zone7",  11 },
    { 8, "8",   "zone8",  12 },
    { 9, "9",   "zone9",  13 },
    {10, "4.5", "zone45", 23 },
};

// SQL query templates
constexpr const char* SQL_CHECKIN_CLEAR =
    "UPDATE assets SET assigned_to = NULL, location_id = 0 WHERE _snipeit_zone_4 = ?;";
constexpr const char* SQL_CHECKIN_STATUS =
    "UPDATE assets SET status_id = 2 WHERE _snipeit_zone_4 = ?;";
constexpr const char* SQL_CHECKOUT_ASSIGN =
    "UPDATE assets SET assigned_to = ?, location_id = ? WHERE _snipeit_zone_4 = ?;";
constexpr const char* SQL_CHECKOUT_STATUS =
    "UPDATE assets SET status_id = 5 WHERE _snipeit_zone_4 = ?;";

} // namespace InventoryConstants
