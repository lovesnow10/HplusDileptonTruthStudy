/*************************************************************************
*              2016.11.11 @SDU C816                                      *
*     File HplusDileptonEvent.h -> Class to describe a dilepton event    *
*************************************************************************/

#ifndef __HPLUSDILEPTONEVENT_H
#define __HPLUSDILEPTONEVENT_H

#include <iostream>
#include <map>
#include <vector>

#include "TLorentzVector.h"

enum class ObjType { B0, B1, B2, B3, Lp = 10, Lm, MET = 20, Np = 30, Nm };

class DilepEvent {
private:
  // vectors for objects
  TLorentzVector *m_b0Momentum;
  TLorentzVector *m_b1Momentum;
  TLorentzVector *m_b2Momentum;
  TLorentzVector *m_b3Momentum;

  TLorentzVector *m_lpMomentum;
  TLorentzVector *m_lmMomentum;

  TLorentzVector *m_metMomentum;
  // map to hold all objects
  std::map<ObjType, TLorentzVector *> m_ObjMap;
  std::map<ObjType, float> m_mv2c10;

public:
  DilepEvent();
  virtual ~DilepEvent(){};

  int SetVector(ObjType type, TLorentzVector *vect);
  TLorentzVector *GetVector(ObjType type);
  int SetBTagging(ObjType type, float mv2c10);
  float GetBTagging(ObjType type);
};

#endif
