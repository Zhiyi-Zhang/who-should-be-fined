#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "isaac.hpp"
#include <iostream>
#include <list>
#include <utility>
#include <vector>

static int FIELD = 100; // the value of x in R%x to drop some rows for receiver
static int TOTAL_RECEIVER = 3; // ID: 1, 2, 3
static double LEAST_MAKE_SENSE_PERCENT = 0.75;
static double POPUlAR_KEYWORD_THRESHOLD = 0.0015;

// Keyword Allocation Loss rate: 1/5, so 4/5 will be allocated to each receiver
static int OT_LOSS_RATE_NUMERATOR = 1;
static int OT_LOSS_RATE_DENOMINATOR = 5;

static inline bool
dropForReceiver(int rowNumber, int receiverID,
                int maskRange, int field = OT_LOSS_RATE_DENOMINATOR)
{
  return rowNumber % field >= (receiverID - 1) * maskRange && rowNumber % field < receiverID * maskRange;
}

// get the keywords with the popularity
std::list<std::pair<uint16_t, double> >
parseKeyWords(const std::string& fileName);

// scan the whole database to calculate the popularity of each keyword
void
obtainPopularity(std::list<std::pair<uint16_t, double> >& keywords, const std::list<std::string>& fileNames);

// get the keywords with the popularity from heatmap
std::list<std::pair<uint16_t, double> >
parseHeatMap(const std::string& fileName);

// get the keywords only
std::list<uint16_t>
parseHeatMapOnlyKeys(const std::string& fileName);

// get the keywords only
std::list<uint16_t>
parseKeyWordsFile(const std::string& fileName);

// return popular keyword list, remaining keywords are in @afterStrip
void
stripPopularRecords(const std::list<std::pair<uint16_t, double> >& keywords, std::list<uint16_t>& afterStrip,
                    std::list<uint16_t>& popularKeys, double threshold = POPUlAR_KEYWORD_THRESHOLD);

// shuffle the list. This fun is cryptographically secured by using ISAAC CSPRNG with /dev/urand seed
void
shuffleList(std::list<uint16_t>& keywords);

// Step1: use row number to determine the rows sent to receiver @receiverID
// Step2: order the selected keywords and append them into the result @forReceiver
void
keyWordsForReceiver(const std::list<uint16_t>& wholeSet, std::list<uint16_t>& forReceiver,
                    int receiverID, int maskRange = OT_LOSS_RATE_NUMERATOR,
                    int field = OT_LOSS_RATE_DENOMINATOR);

// read rows from the dataset into the buf
void
extractKeyWordsRows(const std::list<std::string>& fileNames, const std::list<uint16_t>& keywords, const std::string& outputDir);


#endif // FILE_HANDLER_H
