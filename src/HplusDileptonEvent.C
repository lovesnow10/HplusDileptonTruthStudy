/************************************************************************
*                        2016.11.14 @SDU C816                           *
*   File HplusDileptonEvent.C -> Class to describe a dilepton event     *
************************************************************************/

#include "HplusDileptonEvent.h"

DilepEvent::DilepEvent() {
  m_ObjMap.clear();
  m_mv2c10.clear();
  m_b0Momentum = nullptr;
  m_b1Momentum = nullptr;
  m_b2Momentum = nullptr;
  m_b3Momentum = nullptr;
  m_lmMomentum = nullptr;
  m_lpMomentum = nullptr;
  m_metMomentum = nullptr;
}

int DilepEvent::SetVector(ObjType type, TLorentzVector *vect) {
  m_ObjMap[type] = vect;
  return 0;
}

TLorentzVector *DilepEvent::GetVector(ObjType type) {
  return m_ObjMap.find(type) != m_ObjMap.end() ? m_ObjMap.at(type) : nullptr;
}

int DilepEvent::SetBTagging(ObjType type, float mv2c10) {
  m_mv2c10[type] = mv2c10;
  return 0;
}

float DilepEvent::GetBTagging(ObjType type) {
  return m_mv2c10.find(type) != m_mv2c10.end() ? m_mv2c10.at(type) : -10;
}
