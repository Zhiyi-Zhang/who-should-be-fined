#include "ledger.hpp"

void
Ledger::addRecord(const LedgerRecord& record)
{
  // set new front end
  m_frontEnd = record.getBase64SelfTag();
  // update unsync counters
  m_unSyncRecordCounter++;
  m_unSyncByteCounter += record.m_recordSize;
  // insert the record
  m_ledger.insert(std::pair<std::string, LedgerRecord>(m_frontEnd, record));
}

void
Ledger::prepareSync(uint8_t* syncPayload)
{
  auto it = m_ledger.find(m_frontEnd);
  while (it->second.getBase64SelfTag() != m_syncedPoint && it != m_ledger.end()) {
    memcpy(syncPayload, it->second.m_record, it->second.m_recordSize);
    it = m_ledger.find(it->second.getBase64PreviousRecordTag());
  }
  m_syncedPoint = m_frontEnd;
}