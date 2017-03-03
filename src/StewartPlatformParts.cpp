// Copyright (c) 2017 shoarai

#include "StewartPlatformParts.h"

HexaPlatform::HexaPlatform(CDBL &rad, CDBL &ang)
    : radius(rad), angle(ang), angle2(PI * 2 / 3 - ang) {
  // 球面軸受の初期ベクトルの初期化
  vecE[0].set(radius * cos(angle / 2), radius * sin(angle / 2), 0);
  vecE[1].set(radius * cos(angle / 2), -radius * sin(angle / 2), 0);

  vecE[2].set(-radius * sin(PI / 2 - angle - angle2 / 2),
              -radius * cos(PI / 2 - angle - angle2 / 2), 0);

  vecE[3].set(-radius * cos(angle2 / 2), -radius * sin(angle2 / 2), 0);
  vecE[4].set(-radius * cos(angle2 / 2), radius * sin(angle2 / 2), 0);

  vecE[5].set(-radius * sin(PI / 2 - angle - angle2 / 2),
              radius * cos(PI / 2 - angle - angle2 / 2), 0);
}

BasePlate::BasePlate(CDBL &rad, CDBL &ang)
    : radius(rad), angle(ang), angle2(PI * 2 / 3 - ang) {
  // 球面軸受のベクトルの初期化
  vecS[0].set(radius * cos(angle2 / 2), radius * sin(angle2 / 2), 0);
  vecS[1].set(radius * cos(angle2 / 2), -radius * sin(angle2 / 2), 0);
  vecS[2].set(radius * sin(PI / 2 - angle - angle2 / 2),
              -radius * cos(PI / 2 - angle - angle2 / 2), 0);
  vecS[3].set(-radius * cos(angle / 2), -radius * sin(angle / 2), 0);
  vecS[4].set(-radius * cos(angle / 2), radius * sin(angle / 2), 0);
  vecS[5].set(radius * sin(PI / 2 - angle - angle2 / 2),
              radius * cos(PI / 2 - angle - angle2 / 2), 0);
}
