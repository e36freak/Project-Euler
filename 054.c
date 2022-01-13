#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
  int value;
  char suit;
} card;

enum handtypes {
  high_card, // 2 - 14 10^0
  one_pair, // 20 - 140 10^1
  two_pair, // 300-1400 10^2
  three_of_a_kind, // 2000-14000 10^3
  straight, // 60000 - 140000 10^4
  flush,  // 600000 - 1400000 10^5
  full_house, // 3000000 - 14000000 10^6
  four_of_a_kind, // 20000000 - 140000000 10^7
  straight_flush // 600000000 - 1400000000 10^8
};

int card_val(char cstr[]) {
  switch (cstr[0]) {
    case 'T': return 10;
    case 'J': return 11;
    case 'Q': return 12;
    case 'K': return 13;
    case 'A': return 14;
    default: return cstr[0] - '0';
  }
}

// read each line of input into two hands, each sorted by value
int read_hands(card p1[], card p2[]) {
  char cstr[3];
  card tmp;
  for (int i = 0; i < 5; i++) {
    if (scanf("%s", cstr) != 1) {
      return 0;
    }
    p1[i].value = card_val(cstr);
    p1[i].suit = cstr[1];
    for (int j = i; j > 0 && p1[j].value < p1[j-1].value; j--) {
      tmp = p1[j];
      p1[j] = p1[j-1];
      p1[j-1] = tmp;
    }
  }
  for (int i = 0; i < 5; i++) {
    if (scanf("%s", cstr) != 1) {
      return 0;
    }
    p2[i].value = card_val(cstr);
    p2[i].suit = cstr[1];
    for (int j = i; j > 0 && p2[j].value < p2[j-1].value; j--) {
      tmp = p2[j];
      p2[j] = p2[j-1];
      p2[j-1] = tmp;
    }
  }
  return 1;
}

int is_flush(card hand[]) {
  for (int i = 1; i < 5; i++) {
    if (hand[i].suit != hand[0].suit) {
      return 0;
    }
  }
  return 1;
}

int is_straight(card hand[]) {
  for (int i = 1; i < 5; i++) {
    if (hand[i].value - hand[i-1].value != 1) {
      return 0;
    }
  }
  return 1;
}

int hand_value(card hand[]) {
  int hasflush, hasstraight;
  int dups[15] = {0};
  for (int i = 0; i < 5; i++) {
    dups[hand[i].value]++;
  }
  hasflush = is_flush(hand);
  hasstraight = is_straight(hand);
  if (hasflush && hasstraight) {
    return hand[4].value * pow(10, straight_flush);
  }
  int trips = 0, pairs = 0, high_pair = 0;
  for (int i = 2; i <= 14; i++) {
    if (dups[i] == 4) {
      return i * pow(10, four_of_a_kind);
    } else if (dups[i] == 3) {
      trips = i;
    } else if (dups[i] == 2) {
      pairs++;
      high_pair = i;
    }
  }
  if (trips && pairs) {
    return trips * pow(10, full_house);
  }
  if (hasflush) {
    return hand[4].value * pow(10, flush);
  }
  if (hasstraight) {
    return hand[4].value * pow(10, straight);
  }
  if (trips) {
    return trips * pow(10, three_of_a_kind);
  }
  if (pairs == 2) {
    int low_pair;
    for (int i = 2; i <14; i++) {
      if (dups[i] == 2) {
        low_pair = i;
        break;
      }
    }
    return high_pair * pow(10, two_pair) + low_pair;
  }
  if (pairs) {
    return high_pair * pow(10, one_pair);
  }
  return hand[4].value; // high card
}

int main(void) {
  card p1[5], p2[5];
  int p1val, p2val;
  int ans = 0;
  while (read_hands(p1, p2)) {
    p1val = hand_value(p1);
    p2val = hand_value(p2);
    if (p1val > p2val) {
      ans++;
    } else if (p1val == p2val) {
      for (int i = 4; i >= 0; i--) {
        if (p1[i].value != p2[i].value) {
          if (p1[i].value > p2[i].value) {
            ans++;
          }
          break;
        }
      }
    }
  }
  printf("%d\n", ans);
}
