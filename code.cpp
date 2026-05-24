#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

// ============================================================
//  UTILITY
// ============================================================
void sleep_ms(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

void printLine(string ch = "-", int len = 60) {
    for (int i = 0; i < len; i++) cout << ch;
    cout << endl;
}

void slowPrint(const string& text, int delay = 30) {
    for (char c : text) {
        cout << c << flush;
        sleep_ms(delay);
    }
    cout << endl;
}

void typeWriter(const string& text, int delay = 25) {
    for (char c : text) {
        cout << c << flush;
        sleep_ms(delay);
    }
}

void dramaticPause(int ms = 1500) {
    sleep_ms(ms);
}

int randRange(int lo, int hi) {
    return lo + rand() % (hi - lo + 1);
}

void bloodSplatter() {
    cout << endl;
    typeWriter("                    * ", 40);
    typeWriter("*  ", 80);
    typeWriter("*    ", 60);
    typeWriter("*  ", 90);
    typeWriter("*", 40);
    cout << endl;
    typeWriter("               *   ", 50);
    typeWriter("* * *   ", 30);
    typeWriter("*    ", 70);
    typeWriter("* *", 45);
    cout << endl;
    sleep_ms(400);
}

void screenFlash(const string& msg) {
    cout << "\n\n";
    printLine("!", 60);
    printLine("!", 60);
    cout << "  " << msg << endl;
    printLine("!", 60);
    printLine("!", 60);
    sleep_ms(800);
    cout << "\n";
}

void showSwordArt() {
    cout << endl;
    sleep_ms(200);
    typeWriter("        =====|>                          <|=====", 15);
    cout << endl;
    sleep_ms(600);
    typeWriter("              \\                          /", 15);
    cout << endl;
    sleep_ms(400);
    typeWriter("               \\______________________/", 15);
    cout << endl;
    sleep_ms(800);
    cout << endl;
}

// ============================================================
//  STRUCTS
// ============================================================
struct Weapon {
    string name;
    int minDmg, maxDmg;
};

struct Player {
    string name = "Pradeep";
    int hp = 100, maxHp = 100;
    int stamina = 100, maxStamina = 100;
    int gold = 0;
    int level = 1;
    int xp = 0;
    int xpToNext = 100;
    int defense = 5;
    Weapon weapon = {"Wooden Bokken", 5, 12};
    vector<string> inventory;
    vector<string> completedQuests;
    bool hasHonorBlade = false;
};

struct Enemy {
    string name;
    int hp, maxHp;
    int minDmg, maxDmg;
    int defense;
    int xpReward;
    int goldReward;
    string deathQuote;
};

// ============================================================
//  ENEMIES PER LEVEL
// ============================================================
Enemy makeEnemy(int level) {
    vector<Enemy> pool;

    if (level == 1) {
        pool = {
            {"Kenji the Thief",       40, 40, 4, 9,  2, 30, 50,  "\"I... was just hungry...\""},
            {"Takeshi the Drunkard",  35, 35, 3, 8,  1, 25, 30,  "\"The sake... betrayed me...\""},
            {"Ryota the Pickpocket",  30, 30, 4, 7,  1, 20, 25,  "\"No one ever gave me a chance!\""},
        };
    } else if (level == 2) {
        pool = {
            {"Hiroshi the Bandit",    60, 60, 7, 14, 4, 60, 80,  "\"My clan will avenge me!\""},
            {"Noboru the Deserter",   55, 55, 6, 13, 3, 55, 70,  "\"I should have stayed loyal...\""},
            {"Daichi the Mercenary",  65, 65, 8, 15, 4, 65, 90,  "\"Gold... was never worth this...\""},
        };
    } else if (level == 3) {
        pool = {
            {"Shigeru the Ronin",     80, 80, 10,18, 6, 90, 120, "\"A ronin's fate is to fall...\""},
            {"Kazuki the Shadow",     75, 75, 9, 17, 5, 85, 110, "\"Darkness... claims me...\""},
            {"Fumio the Betrayer",    85, 85, 11,19, 6, 95, 130, "\"I betrayed my lord for nothing!\""},
        };
    } else if (level == 4) {
        pool = {
            {"Masato the Warlord",   110,110, 13,22, 8,130, 160, "\"My army... will live on...\""},
            {"Genzo the Poisoner",   100,100, 12,20, 7,120, 150, "\"Poison is the coward's art... I know...\""},
            {"Toshiro the Butcher",  115,115, 14,23, 9,135, 170, "\"I bathed in blood... and drowned in it...\""},
        };
    } else {
        pool = {
            {"Orochi the Demon Blade",150,150,16,28,12,200,300, "\"Impossible... a foreigner fells me...\""},
        };
    }

    return pool[rand() % pool.size()];
}

Enemy makeBoss(int level) {
    if (level == 1)
        return {"Jinpachi the Scarred",    70,  70, 10, 16,  4,  80, 150,
                "\"You fight well... stranger. Remember my name.\""};
    if (level == 2)
        return {"Raijin the Thunder Fist", 100, 100, 13, 20,  6, 130, 220,
                "\"Even thunder... must bow to the blade.\""};
    if (level == 3)
        return {"Muramasa the Mad Priest", 130, 130, 15, 24,  8, 180, 300,
                "\"The gods have abandoned me... as I abandoned them.\""};
    if (level == 4)
        return {"Katsuro the Shadow Shogun",165,165, 18, 27, 11, 240, 400,
                "\"A shogun... defeated by a wanderer. History is cruel.\""};
    return {"Akuma-no-Ken, The Devil Swordsman",
                                             220, 220, 22, 35, 15, 500, 600,
                "\"You... Pradeep... are the greatest warrior I have faced. I die... in honor.\""};
}

// ============================================================
//  DISPLAY
// ============================================================
void showStats(const Player& p) {
    printLine("=");
    cout << "  SAMURAI PRADEEP  |  Level: " << p.level
         << "  |  XP: " << p.xp << "/" << p.xpToNext << endl;
    cout << "  HP: " << p.hp << "/" << p.maxHp
         << "  |  Stamina: " << p.stamina << "/" << p.maxStamina
         << "  |  Gold: " << p.gold << endl;
    cout << "  Weapon: " << p.weapon.name
         << " [" << p.weapon.minDmg << "-" << p.weapon.maxDmg << " dmg]"
         << "  |  Defense: " << p.defense << endl;
    printLine("=");
}

void showEnemyBar(const Enemy& e) {
    cout << "  [" << e.name << "]  HP: " << e.hp << "/" << e.maxHp << endl;
}

// ============================================================
//  LEVEL UP
// ============================================================
void checkLevelUp(Player& p) {
    while (p.xp >= p.xpToNext) {
        p.xp -= p.xpToNext;
        p.level++;
        p.xpToNext = p.level * 100;
        p.maxHp += 20;
        p.hp = p.maxHp;
        p.maxStamina += 10;
        p.stamina = p.maxStamina;
        p.defense += 2;
        printLine("*");
        slowPrint("  *** LEVEL UP! You are now Level " + to_string(p.level) + " ***");
        slowPrint("  HP increased! Defense increased! Stamina increased!");
        printLine("*");
        sleep_ms(800);
    }
}

// ============================================================
//  COMBAT
// ============================================================
bool fight(Player& p, Enemy e, bool isBoss = false) {
    printLine("#");
    if (isBoss) slowPrint("  !! BOSS BATTLE: " + e.name + " !!");
    else        slowPrint("  ENEMY: " + e.name + " approaches!");
    printLine("#");
    sleep_ms(500);

    while (e.hp > 0 && p.hp > 0) {
        cout << endl;
        showEnemyBar(e);
        cout << "  Your HP: " << p.hp << " | Stamina: " << p.stamina << endl;
        cout << endl;
        cout << "  [1] Strike        [2] Heavy Strike (costs 20 stamina)" << endl;
        cout << "  [3] Parry & Counter (costs 15 stamina)  [4] Drink Herb Tea (if owned)" << endl;
        cout << "  Choice: ";

        int choice; cin >> choice;

        int playerDmg = 0;
        bool extraTurn = false;

        if (choice == 1) {
            playerDmg = randRange(p.weapon.minDmg, p.weapon.maxDmg);
            int actualDmg = max(0, playerDmg - e.defense);
            e.hp -= actualDmg;
            slowPrint("  You strike! Dealt " + to_string(actualDmg) + " damage.");

        } else if (choice == 2) {
            if (p.stamina < 20) {
                slowPrint("  Not enough stamina! You stumble...");
            } else {
                p.stamina -= 20;
                playerDmg = randRange(p.weapon.minDmg * 2, p.weapon.maxDmg * 2);
                int actualDmg = max(0, playerDmg - e.defense);
                e.hp -= actualDmg;
                slowPrint("  HEAVY STRIKE! Dealt " + to_string(actualDmg) + " damage!");
            }

        } else if (choice == 3) {
            if (p.stamina < 15) {
                slowPrint("  Not enough stamina to parry!");
            } else {
                p.stamina -= 15;
                int roll = randRange(1, 100);
                if (roll > 40) {
                    slowPrint("  You parry perfectly and counter-attack!");
                    int counterDmg = max(0, randRange(p.weapon.minDmg, p.weapon.maxDmg) + 5 - e.defense);
                    e.hp -= counterDmg;
                    slowPrint("  Counter dealt " + to_string(counterDmg) + " damage!");
                    extraTurn = true;
                } else {
                    slowPrint("  Parry failed! You are open to attack!");
                }
            }

        } else if (choice == 4) {
            bool hasHerb = false;
            for (int i = 0; i < (int)p.inventory.size(); i++) {
                if (p.inventory[i] == "Herb Tea") {
                    p.inventory.erase(p.inventory.begin() + i);
                    int heal = randRange(20, 35);
                    p.hp = min(p.maxHp, p.hp + heal);
                    slowPrint("  You drink Herb Tea and recover " + to_string(heal) + " HP!");
                    hasHerb = true;
                    break;
                }
            }
            if (!hasHerb) slowPrint("  You have no Herb Tea!");

        } else {
            slowPrint("  Invalid choice. You hesitate!");
        }

        if (e.hp <= 0) break;
        if (extraTurn) { slowPrint("  Enemy is staggered! You gain another action!"); continue; }

        sleep_ms(400);
        int enemyDmg = randRange(e.minDmg, e.maxDmg);
        int actualEnemyDmg = max(0, enemyDmg - p.defense);

        if (randRange(1, 100) > 70) {
            slowPrint("  " + e.name + " unleashes a FIERCE attack!");
            actualEnemyDmg = (int)(actualEnemyDmg * 1.5);
        } else {
            slowPrint("  " + e.name + " attacks you!");
        }

        p.hp -= actualEnemyDmg;
        slowPrint("  You take " + to_string(actualEnemyDmg) + " damage!");

        p.stamina = min(p.maxStamina, p.stamina + 8);
    }

    cout << endl;
    if (p.hp <= 0) {
        printLine("!");
        slowPrint("  You have fallen in battle...");
        printLine("!");
        return false;
    }

    printLine("~");
    slowPrint("  " + e.deathQuote);
    slowPrint("  Victory! You defeated " + e.name + "!");
    p.xp += e.xpReward;
    p.gold += e.goldReward;
    slowPrint("  +" + to_string(e.xpReward) + " XP  |  +" + to_string(e.goldReward) + " Gold");
    printLine("~");
    checkLevelUp(p);
    sleep_ms(600);
    return true;
}

// ============================================================
//  SHOP
// ============================================================
void visitShop(Player& p, int gameLevel) {
    printLine("=");
    slowPrint("  BLACKSMITH & MERCHANT");
    printLine("=");

    struct ShopItem { string name; int cost; string type; };
    vector<ShopItem> items;

    if (gameLevel == 1) {
        items = {
            {"Iron Katana [8-18 dmg]",   80,  "weapon1"},
            {"Herb Tea (heal 20-35 HP)", 30,  "herbtea"},
            {"Leather Armor (+3 def)",   60,  "armor1"},
        };
    } else if (gameLevel == 2) {
        items = {
            {"Steel Katana [12-24 dmg]", 150, "weapon2"},
            {"Herb Tea (heal 20-35 HP)", 30,  "herbtea"},
            {"Chain Mail (+5 def)",      120, "armor2"},
            {"Elixir (heal 50 HP)",      80,  "elixir"},
        };
    } else if (gameLevel == 3) {
        items = {
            {"Demon Blade [17-30 dmg]",  250, "weapon3"},
            {"Herb Tea (heal 20-35 HP)", 30,  "herbtea"},
            {"Samurai Armor (+8 def)",   200, "armor3"},
            {"Elixir (heal 50 HP)",      80,  "elixir"},
        };
    } else {
        items = {
            {"Cursed Odachi [22-38 dmg]",400, "weapon4"},
            {"Herb Tea (heal 20-35 HP)", 30,  "herbtea"},
            {"Shogun Armor (+12 def)",   350, "armor4"},
            {"Elixir (heal 50 HP)",      80,  "elixir"},
            {"Full Restore (full HP)",   200, "fullhp"},
        };
    }

    bool shopping = true;
    while (shopping) {
        cout << endl;
        cout << "  Your Gold: " << p.gold << endl;
        cout << endl;
        for (int i = 0; i < (int)items.size(); i++)
            cout << "  [" << i+1 << "] " << items[i].name << "  - " << items[i].cost << " Gold" << endl;
        cout << "  [0] Leave shop" << endl;
        cout << "  Choice: ";

        int c; cin >> c;
        if (c == 0) { shopping = false; break; }
        if (c < 1 || c > (int)items.size()) { slowPrint("  Invalid choice."); continue; }

        ShopItem& item = items[c-1];
        if (p.gold < item.cost) { slowPrint("  Not enough gold!"); continue; }

        p.gold -= item.cost;

        if (item.type == "herbtea")  { p.inventory.push_back("Herb Tea"); slowPrint("  Herb Tea added to inventory!"); }
        else if (item.type == "elixir") { p.hp = min(p.maxHp, p.hp + 50); slowPrint("  Elixir consumed! +50 HP!"); }
        else if (item.type == "fullhp") { p.hp = p.maxHp; p.stamina = p.maxStamina; slowPrint("  Full Restore! HP and Stamina fully recovered!"); }
        else if (item.type == "armor1") { p.defense += 3; slowPrint("  Leather Armor equipped! +3 Defense!"); }
        else if (item.type == "armor2") { p.defense += 5; slowPrint("  Chain Mail equipped! +5 Defense!"); }
        else if (item.type == "armor3") { p.defense += 8; slowPrint("  Samurai Armor equipped! +8 Defense!"); }
        else if (item.type == "armor4") { p.defense += 12; slowPrint("  Shogun Armor equipped! +12 Defense!"); }
        else if (item.type == "weapon1") { p.weapon = {"Iron Katana",    8,  18}; slowPrint("  Iron Katana equipped!"); }
        else if (item.type == "weapon2") { p.weapon = {"Steel Katana",   12, 24}; slowPrint("  Steel Katana equipped!"); }
        else if (item.type == "weapon3") { p.weapon = {"Demon Blade",    17, 30}; slowPrint("  Demon Blade equipped!"); }
        else if (item.type == "weapon4") { p.weapon = {"Cursed Odachi",  22, 38}; slowPrint("  Cursed Odachi equipped!"); }
    }
}

// ============================================================
//  QUESTS
// ============================================================
void doQuest(Player& p, int gameLevel) {
    printLine(">");
    string questTitle, questDesc, questReward;
    bool alreadyDone = false;

    if (gameLevel == 1) {
        questTitle = "The Missing Merchant";
        questDesc  = "Old merchant Ichiro has gone missing near the eastern forest. Find him.";
        questReward= "Herb Tea x2 + 40 Gold";
        for (auto& q : p.completedQuests) if (q == questTitle) alreadyDone = true;
    } else if (gameLevel == 2) {
        questTitle = "Bandits of Kurokawa Pass";
        questDesc  = "Villagers are terrorized by Hiroshi's bandit gang at Kurokawa Pass. Drive them out.";
        questReward= "Steel Dagger (+3 min dmg) + 100 Gold";
        for (auto& q : p.completedQuests) if (q == questTitle) alreadyDone = true;
    } else if (gameLevel == 3) {
        questTitle = "The Cursed Temple of Izanami";
        questDesc  = "A mad priest has defiled the Temple of Izanami. Cleanse it.";
        questReward= "Samurai Helm (+5 def) + 200 Gold";
        for (auto& q : p.completedQuests) if (q == questTitle) alreadyDone = true;
    } else if (gameLevel == 4) {
        questTitle = "The Shadow Shogun's Decree";
        questDesc  = "Katsuro has enslaved three villages. Defeat his lieutenants and free the people.";
        questReward= "Honor Blade (legendary) + 300 Gold";
        for (auto& q : p.completedQuests) if (q == questTitle) alreadyDone = true;
    } else {
        questTitle = "Final Quest: The Devil's Last Stand";
        questDesc  = "Akuma-no-Ken awaits you at Mount Fuji's peak. End this.";
        questReward= "Glory, Honor, and Legend";
        for (auto& q : p.completedQuests) if (q == questTitle) alreadyDone = true;
    }

    if (alreadyDone) {
        slowPrint("  [Quest already completed: " + questTitle + "]");
        printLine(">");
        return;
    }

    slowPrint("  QUEST: " + questTitle);
    slowPrint("  " + questDesc);
    slowPrint("  Reward: " + questReward);
    printLine(">");
    cout << "  [1] Accept Quest  [2] Decline" << endl;
    cout << "  Choice: ";
    int c; cin >> c;
    if (c != 1) { slowPrint("  You declined the quest."); return; }

    slowPrint("  You set out on the quest...");
    sleep_ms(600);

    for (int i = 0; i < 2; i++) {
        sleep_ms(400);
        Enemy e = makeEnemy(gameLevel);
        slowPrint("  A foe blocks your path: " + e.name);
        bool survived = fight(p, e);
        if (!survived) return;
        if (p.hp <= 0) return;
    }

    p.completedQuests.push_back(questTitle);
    slowPrint("  Quest Complete: " + questTitle + "!");

    if (gameLevel == 1) {
        p.inventory.push_back("Herb Tea");
        p.inventory.push_back("Herb Tea");
        p.gold += 40;
        slowPrint("  Received: Herb Tea x2 + 40 Gold");
    } else if (gameLevel == 2) {
        p.weapon.minDmg += 3;
        p.gold += 100;
        slowPrint("  Received: +3 min damage upgrade + 100 Gold");
    } else if (gameLevel == 3) {
        p.defense += 5;
        p.gold += 200;
        slowPrint("  Received: +5 Defense (Samurai Helm) + 200 Gold");
    } else if (gameLevel == 4) {
        p.hasHonorBlade = true;
        p.weapon = {"Honor Blade", 25, 42};
        p.gold += 300;
        slowPrint("  Received: HONOR BLADE EQUIPPED! + 300 Gold");
    } else {
        slowPrint("  You have earned your legend, Pradeep.");
    }
}

// ============================================================
//  LEVEL INTRO
// ============================================================
void levelIntro(int lvl) {
    printLine("=");
    if (lvl == 1) {
        slowPrint("  LEVEL 1 - THE VILLAGE OF KUROKAWA");
        slowPrint("  Year 1600. You, Pradeep, arrive at the dust-covered");
        slowPrint("  village of Kurokawa. Petty thieves and drunk brawlers");
        slowPrint("  roam the streets. This is where your legend begins.");
    } else if (lvl == 2) {
        slowPrint("  LEVEL 2 - KUROKAWA PASS");
        slowPrint("  A narrow mountain pass controlled by Hiroshi's bandits.");
        slowPrint("  Merchants dare not travel. You will clear the way.");
    } else if (lvl == 3) {
        slowPrint("  LEVEL 3 - THE CURSED FOREST & IZANAMI TEMPLE");
        slowPrint("  Ancient trees hide shadows with blades. A mad priest");
        slowPrint("  has unleashed dark forces. Steel and spirit will be tested.");
    } else if (lvl == 4) {
        slowPrint("  LEVEL 4 - THE WARLORD'S DOMAIN");
        slowPrint("  Three villages burn under the Shadow Shogun's rule.");
        slowPrint("  Warlords, poisoners, and butchers guard his castle.");
        slowPrint("  You must cut through them all.");
    } else {
        slowPrint("  LEVEL 5 - MOUNT FUJI'S PEAK - THE FINAL BATTLE");
        slowPrint("  Snow and ash mix in the air. Akuma-no-Ken,");
        slowPrint("  the Devil Swordsman, stands at the summit.");
        slowPrint("  One sword. One warrior. One destiny.");
        slowPrint("  Pradeep... this is your moment.");
    }
    printLine("=");
    sleep_ms(1000);
}

// ============================================================
//  PLAY ONE GAME LEVEL
// ============================================================
bool playLevel(Player& p, int gameLevel) {
    levelIntro(gameLevel);

    int enemyCount = 2 + gameLevel;

    for (int i = 0; i < enemyCount; i++) {
        showStats(p);
        cout << endl;
        cout << "  CHAPTER " << gameLevel << " - Encounter " << i+1 << "/" << enemyCount << endl;
        cout << endl;
        cout << "  [1] Explore & Fight  [2] Visit Shop  [3] Take Quest  [4] Rest (+15 HP, -20 Gold)" << endl;
        cout << "  Choice: ";
        int c; cin >> c;

        if (c == 2) {
            visitShop(p, gameLevel);
            i--;
            continue;
        } else if (c == 3) {
            doQuest(p, gameLevel);
            if (p.hp <= 0) return false;
            i--;
            continue;
        } else if (c == 4) {
            if (p.gold >= 20) {
                p.gold -= 20;
                p.hp = min(p.maxHp, p.hp + 15);
                p.stamina = min(p.maxStamina, p.stamina + 20);
                slowPrint("  You rest at a teahouse. +15 HP, +20 Stamina.");
            } else {
                slowPrint("  Not enough gold to rest.");
            }
            i--;
            continue;
        }

        Enemy e = makeEnemy(gameLevel);
        bool survived = fight(p, e);
        if (!survived || p.hp <= 0) return false;
    }

    cout << endl;
    slowPrint("  A dark presence looms. The boss awaits...");
    sleep_ms(800);
    showStats(p);
    cout << "  [1] Challenge the Boss  [2] Visit Shop first  [3] Rest (20 Gold)" << endl;
    cout << "  Choice: ";
    int bc; cin >> bc;

    if (bc == 2) { visitShop(p, gameLevel); }
    else if (bc == 3) {
        if (p.gold >= 20) { p.gold -= 20; p.hp = min(p.maxHp, p.hp + 15); slowPrint("  Rested. +15 HP."); }
        else slowPrint("  Not enough gold.");
    }

    Enemy boss = makeBoss(gameLevel);
    bool survived = fight(p, boss, true);
    if (!survived || p.hp <= 0) return false;

    printLine("*");
    slowPrint("  LEVEL " + to_string(gameLevel) + " COMPLETE!");
    slowPrint("  Pradeep sheathes his blade. The path ahead grows darker.");
    printLine("*");
    sleep_ms(1000);
    return true;
}

// ============================================================
//  ENDING
// ============================================================
void showEnding(const Player& p) {
    printLine("=");
    slowPrint("  THE LEGEND OF PRADEEP");
    printLine("=");
    slowPrint("  Akuma-no-Ken crumbles to the snow-covered ground.");
    slowPrint("  His sword clatters. Silence falls over Mount Fuji.");
    slowPrint("");
    slowPrint("  Pradeep looks out over Japan -- a land finally free");
    slowPrint("  from the shadow of tyrants. No master. No chains.");
    slowPrint("  Only the wind, the blade, and the open road.");
    slowPrint("");
    slowPrint("  The villagers of Kurokawa will sing his name.");
    slowPrint("  The merchants of the pass will honor him.");
    slowPrint("  The priests of Izanami will light incense for him.");
    slowPrint("  And the freed slaves will name their children Pradeep.");
    slowPrint("");
    slowPrint("  He is not Japanese. He carries no clan mon.");
    slowPrint("  But Japan will remember him as one of its greatest samurai.");
    slowPrint("");
    cout << "  Final Stats:" << endl;
    cout << "    Name    : " << p.name << endl;
    cout << "    Level   : " << p.level << endl;
    cout << "    Gold    : " << p.gold << endl;
    cout << "    Weapon  : " << p.weapon.name << endl;
    cout << "    Defense : " << p.defense << endl;
    cout << "    Quests  : " << p.completedQuests.size() << " completed" << endl;
    printLine("=");
    slowPrint("  ~ THE END ~");
    printLine("=");
}

// ============================================================
//  DARK OPENING STORY
// ============================================================
void playOpeningStory(Player& p) {

    // === TITLE DROP ===
    cout << "\n\n\n";
    sleep_ms(300);
    printLine("=", 60);
    cout << endl;
    sleep_ms(300);
    typeWriter("          K  A  T  A  N  A     N  O", 60);
    cout << endl;
    sleep_ms(400);
    cout << endl;
    typeWriter("              P  R  A  D  E  E  P", 80);
    cout << endl;
    sleep_ms(500);
    cout << endl;
    printLine("=", 60);
    sleep_ms(600);
    cout << endl;
    typeWriter("                  Year 1600.", 40);
    cout << endl;
    sleep_ms(800);
    typeWriter("               Sengoku Jidai.", 40);
    cout << endl;
    sleep_ms(800);
    typeWriter("          The Age of Warring States.", 40);
    cout << endl;
    sleep_ms(1000);
    cout << endl;
    typeWriter("        Japan is drowning in its own blood.", 35);
    cout << endl;
    sleep_ms(1200);
    cout << endl;

    // === SCENE 1: THE NIGHT OF FIRE ===
    printLine("-", 60);
    typeWriter("  CHAPTER ZERO  --  THE NIGHT EVERYTHING BURNED", 30);
    cout << endl;
    printLine("-", 60);
    sleep_ms(600);
    cout << endl;

    typeWriter("  It was the smell that woke you.", 30);
    sleep_ms(800); cout << endl;
    typeWriter("  Not smoke.", 40);
    sleep_ms(600); cout << endl;
    typeWriter("  Smoke has a kind of warmth to it.", 30);
    sleep_ms(700); cout << endl;
    typeWriter("  This was different.", 35);
    sleep_ms(700); cout << endl;
    cout << endl;
    typeWriter("  This was burning FLESH.", 25);
    sleep_ms(1200); cout << endl;

    bloodSplatter();

    typeWriter("  You opened your eyes.", 30);
    sleep_ms(600); cout << endl;
    typeWriter("  The merchant caravan you had been guarding --", 30);
    sleep_ms(500); cout << endl;
    typeWriter("  twelve wagons, thirty-one people --", 30);
    sleep_ms(500); cout << endl;
    typeWriter("  was GONE.", 25);
    sleep_ms(1000); cout << endl;
    cout << endl;
    typeWriter("  Not robbed.", 35);
    sleep_ms(500); cout << endl;
    typeWriter("  Not scattered.", 35);
    sleep_ms(500); cout << endl;
    typeWriter("  Gone.", 35);
    sleep_ms(800); cout << endl;
    cout << endl;
    typeWriter("  Ash and charred bone were all that remained.", 30);
    sleep_ms(800); cout << endl;
    typeWriter("  And a single black arrow lodged in the earth,", 30);
    sleep_ms(500); cout << endl;
    typeWriter("  inches from your sleeping head.", 30);
    sleep_ms(1000); cout << endl;
    cout << endl;

    screenFlash("SOMEONE LEFT YOU ALIVE. ON PURPOSE.");

    typeWriter("  A warning.", 35);
    sleep_ms(700); cout << endl;
    typeWriter("  Or an invitation.", 35);
    sleep_ms(1000); cout << endl;
    cout << endl;

    cout << "  Press ENTER to continue..." << endl;
    cin.ignore(); cin.get();

    // === SCENE 2: THE SURVIVOR ===
    cout << endl;
    printLine("-", 60);
    typeWriter("  SCENE II  --  THE ONLY WITNESS", 30);
    cout << endl;
    printLine("-", 60);
    sleep_ms(500); cout << endl;

    typeWriter("  Among the wreckage, something moved.", 30);
    sleep_ms(700); cout << endl;
    cout << endl;
    typeWriter("  A boy. No older than twelve.", 30);
    sleep_ms(700); cout << endl;
    typeWriter("  His left hand was gone at the wrist.", 30);
    sleep_ms(900); cout << endl;
    typeWriter("  Cauterized. Deliberately.", 30);
    sleep_ms(1000); cout << endl;
    cout << endl;
    typeWriter("  He looked at you with the eyes of someone", 30);
    sleep_ms(500); cout << endl;
    typeWriter("  who had already decided to die", 30);
    sleep_ms(500); cout << endl;
    typeWriter("  but hadn't yet figured out how.", 30);
    sleep_ms(1200); cout << endl;
    cout << endl;
    typeWriter("  \"They took my sister,\" he whispered.", 30);
    sleep_ms(700); cout << endl;
    typeWriter("  \"The men with the black crests.", 30);
    sleep_ms(500); cout << endl;
    typeWriter("   They laughed while they did it.\"", 30);
    sleep_ms(1000); cout << endl;
    cout << endl;
    typeWriter("  He pressed something into your hand.", 30);
    sleep_ms(700); cout << endl;
    typeWriter("  A cloth badge. Black. A serpent eating its own tail.", 30);
    sleep_ms(800); cout << endl;
    cout << endl;

    screenFlash("YOU RECOGNIZE THE SYMBOL. OROCHI CLAN.");

    typeWriter("  The most feared criminal syndicate in western Japan.", 30);
    sleep_ms(700); cout << endl;
    typeWriter("  They don't leave witnesses.", 30);
    sleep_ms(700); cout << endl;
    typeWriter("  Except when they want someone to suffer.", 30);
    sleep_ms(1000); cout << endl;
    cout << endl;

    // === CHOICE 1 ===
    printLine("~", 60);
    typeWriter("  The boy is dying. He needs care you cannot give.", 30);
    cout << endl;
    typeWriter("  But his words are the only lead you have.", 30);
    cout << endl;
    cout << endl;
    typeWriter("  What do you do?", 30);
    cout << endl;
    printLine("~", 60);
    cout << endl;
    cout << "  [1] Carry him to the nearest village." << endl;
    cout << "      You lose time but gain his trust and a name." << endl;
    cout << "      (+10 max HP)" << endl;
    cout << endl;
    cout << "  [2] Bind his wound and leave him supplies." << endl;
    cout << "      Cold, but you must move fast." << endl;
    cout << "      (+15 Stamina, +30 Gold)" << endl;
    cout << endl;
    cout << "  [3] Sit with him until he speaks everything he knows." << endl;
    cout << "      Dawn breaks. Danger rises." << endl;
    cout << "      (+2 Defense)" << endl;
    cout << endl;
    cout << "  Choice: ";

    int c1; cin >> c1;
    cout << endl;

    if (c1 == 1) {
        typeWriter("  You lift him without a word.", 30);
        sleep_ms(700); cout << endl;
        typeWriter("  He is lighter than he should be.", 30);
        sleep_ms(700); cout << endl;
        typeWriter("  At Kurokawa you leave him with a healer named Hana.", 30);
        sleep_ms(700); cout << endl;
        typeWriter("  Before you leave, he grips your sleeve:", 30);
        sleep_ms(600); cout << endl;
        cout << endl;
        typeWriter("  \"His name is Katsuro. He wears a silver mask.\"", 30);
        sleep_ms(1000); cout << endl;
        cout << endl;
        typeWriter("  A name. A face. A target.", 30);
        sleep_ms(800); cout << endl;
        p.maxHp += 10;
        p.hp = p.maxHp;
        slowPrint("\n  >> Max HP +10 (The boy's survival hardens your resolve.)");

    } else if (c1 == 2) {
        typeWriter("  You tear your sleeve into bandages.", 30);
        sleep_ms(600); cout << endl;
        typeWriter("  Leave your water skin. Leave your dried fish.", 30);
        sleep_ms(700); cout << endl;
        typeWriter("  You do not look back.", 30);
        sleep_ms(800); cout << endl;
        cout << endl;
        typeWriter("  Emotion is a blade that cuts its own wielder.", 30);
        sleep_ms(700); cout << endl;
        typeWriter("  You learned that a long time ago.", 30);
        sleep_ms(1000); cout << endl;
        p.maxStamina += 15;
        p.stamina = p.maxStamina;
        p.gold += 30;
        slowPrint("\n  >> Max Stamina +15, Gold +30 (Cold efficiency. Ruthless clarity.)");

    } else {
        typeWriter("  You sit in the ash.", 30);
        sleep_ms(600); cout << endl;
        typeWriter("  You listen.", 30);
        sleep_ms(700); cout << endl;
        typeWriter("  The boy speaks for two hours.", 30);
        sleep_ms(700); cout << endl;
        typeWriter("  Routes. Faces. How many guards. How they move.", 30);
        sleep_ms(800); cout << endl;
        typeWriter("  By the time he loses consciousness,", 30);
        sleep_ms(600); cout << endl;
        typeWriter("  the sun is bleeding red on the horizon.", 30);
        sleep_ms(900); cout << endl;
        cout << endl;
        typeWriter("  And you have a map drawn in ash", 30);
        sleep_ms(600); cout << endl;
        typeWriter("  on the back of a dead man's coat.", 30);
        sleep_ms(1000); cout << endl;
        p.defense += 2;
        slowPrint("\n  >> Defense +2 (Knowledge is the strongest armor.)");
    }

    sleep_ms(800);
    cout << endl;
    cout << "  Press ENTER to continue..." << endl;
    cin.ignore(); cin.get();

    // === SCENE 3: KUROKAWA ===
    cout << endl;
    printLine("-", 60);
    typeWriter("  SCENE III  --  KUROKAWA", 30);
    cout << endl;
    printLine("-", 60);
    sleep_ms(500); cout << endl;

    typeWriter("  Kurokawa is a village that has forgotten", 30);
    sleep_ms(600); cout << endl;
    typeWriter("  what safety feels like.", 30);
    sleep_ms(700); cout << endl;
    cout << endl;
    typeWriter("  The gates are unguarded.", 30);
    sleep_ms(600); cout << endl;
    typeWriter("  The wells are dry.", 30);
    sleep_ms(600); cout << endl;
    typeWriter("  Children do not play in the streets.", 30);
    sleep_ms(700); cout << endl;
    cout << endl;
    typeWriter("  An old woman sits outside a burned shrine.", 30);
    sleep_ms(600); cout << endl;
    typeWriter("  She is cleaning a wound on her forearm", 30);
    sleep_ms(600); cout << endl;
    typeWriter("  with the calm detachment of someone", 30);
    sleep_ms(600); cout << endl;
    typeWriter("  for whom pain has become routine.", 30);
    sleep_ms(900); cout << endl;
    cout << endl;
    typeWriter("  She looks up at you. No fear. No hope either.", 30);
    sleep_ms(800); cout << endl;
    cout << endl;
    typeWriter("  \"Another wanderer,\" she says.", 30);
    sleep_ms(600); cout << endl;
    typeWriter("  \"They always come. They always leave.\"", 30);
    sleep_ms(1000); cout << endl;
    cout << endl;
    typeWriter("  \"The Orochi men came three nights ago.\"", 30);
    sleep_ms(700); cout << endl;
    typeWriter("  \"Took the young. Left the rest to remember.\"", 30);
    sleep_ms(900); cout << endl;
    cout << endl;
    typeWriter("  She points a crooked finger at the road north.", 30);
    sleep_ms(700); cout << endl;
    typeWriter("  \"That road leads to their first outpost.\"", 30);
    sleep_ms(700); cout << endl;
    typeWriter("  \"No one who goes that way comes back.\"", 30);
    sleep_ms(1000); cout << endl;
    cout << endl;
    typeWriter("  She resumes cleaning her wound.", 30);
    sleep_ms(700); cout << endl;
    typeWriter("  Conversation over.", 30);
    sleep_ms(1000); cout << endl;
    cout << endl;

    // === CHOICE 2: ORIGIN ===
    printLine("~", 60);
    typeWriter("  \"No one who goes that way comes back.\"", 30);
    cout << endl;
    cout << endl;
    typeWriter("  You think about WHY you can survive what others cannot.", 30);
    cout << endl;
    typeWriter("  What made Pradeep a warrior?", 30);
    cout << endl;
    printLine("~", 60);
    cout << endl;
    cout << "  [1] You were a soldier. Trained from age eight." << endl;
    cout << "      War is your language." << endl;
    cout << "      (+15 max HP, +3 Defense)" << endl;
    cout << endl;
    cout << "  [2] You were a street fighter. No training, just survival." << endl;
    cout << "      Brutal and unpredictable." << endl;
    cout << "      (+8 min dmg, +4 max dmg)" << endl;
    cout << endl;
    cout << "  [3] You were a monk's student. Discipline over power." << endl;
    cout << "      (+20 max Stamina, start with 2 Herb Teas)" << endl;
    cout << endl;
    cout << "  Choice: ";

    int c2; cin >> c2;
    cout << endl;

    if (c2 == 1) {
        typeWriter("  You were seven years old when the general", 30);
        sleep_ms(600); cout << endl;
        typeWriter("  pulled you from the burning village", 30);
        sleep_ms(600); cout << endl;
        typeWriter("  and handed you a wooden training sword.", 30);
        sleep_ms(800); cout << endl;
        cout << endl;
        typeWriter("  \"Cry later,\" he said. \"Train now.\"", 30);
        sleep_ms(900); cout << endl;
        cout << endl;
        typeWriter("  You cried later.", 30);
        sleep_ms(600); cout << endl;
        typeWriter("  Then you stopped.", 30);
        sleep_ms(1000); cout << endl;
        p.maxHp += 15;
        p.hp = p.maxHp;
        p.defense += 3;
        slowPrint("\n  >> Max HP +15, Defense +3 (A soldier's body. A soldier's scars.)");

    } else if (c2 == 2) {
        typeWriter("  No dojo. No master. No ceremony.", 30);
        sleep_ms(600); cout << endl;
        typeWriter("  You learned to fight in the alleys", 30);
        sleep_ms(600); cout << endl;
        typeWriter("  where the rules are: don't die.", 30);
        sleep_ms(800); cout << endl;
        cout << endl;
        typeWriter("  Your style is ugly. Effective.", 30);
        sleep_ms(700); cout << endl;
        typeWriter("  You've been underestimated your entire life.", 30);
        sleep_ms(700); cout << endl;
        typeWriter("  You've buried everyone who did.", 30);
        sleep_ms(1000); cout << endl;
        p.weapon.minDmg += 8;
        p.weapon.maxDmg += 4;
        slowPrint("\n  >> Weapon Damage +8 min / +4 max (Street violence has no elegance. Only results.)");

    } else {
        typeWriter("  Master Devraj found you unconscious on the temple steps.", 30);
        sleep_ms(700); cout << endl;
        typeWriter("  He did not ask where you came from.", 30);
        sleep_ms(700); cout << endl;
        cout << endl;
        typeWriter("  For eleven years he taught you", 30);
        sleep_ms(600); cout << endl;
        typeWriter("  that the body is only as strong", 30);
        sleep_ms(600); cout << endl;
        typeWriter("  as the stillness behind it.", 30);
        sleep_ms(1000); cout << endl;
        cout << endl;
        typeWriter("  You repaid him by leaving.", 30);
        sleep_ms(800); cout << endl;
        typeWriter("  He repaid you by not trying to stop you.", 30);
        sleep_ms(1000); cout << endl;
        p.maxStamina += 20;
        p.stamina = p.maxStamina;
        p.inventory.push_back("Herb Tea");
        p.inventory.push_back("Herb Tea");
        slowPrint("\n  >> Max Stamina +20, Herb Tea x2 (Discipline is a weapon that never dulls.)");
    }

    sleep_ms(800);
    cout << endl;
    cout << "  Press ENTER to continue..." << endl;
    cin.ignore(); cin.get();

    // === SCENE 4: THE FIRST GATE ===
    cout << endl;
    printLine("-", 60);
    typeWriter("  SCENE IV  --  THE FIRST GATE", 30);
    cout << endl;
    printLine("-", 60);
    sleep_ms(500); cout << endl;

    typeWriter("  The northern road is exactly as the old woman described.", 30);
    sleep_ms(700); cout << endl;
    typeWriter("  Quiet. Too quiet.", 30);
    sleep_ms(800); cout << endl;
    cout << endl;
    typeWriter("  The Orochi guard at the checkpoint", 30);
    sleep_ms(600); cout << endl;
    typeWriter("  is picking his teeth with a knife.", 30);
    sleep_ms(700); cout << endl;
    typeWriter("  The knife has dried blood on it.", 30);
    sleep_ms(700); cout << endl;
    typeWriter("  He doesn't bother to stand when he sees you.", 30);
    sleep_ms(800); cout << endl;
    cout << endl;
    typeWriter("  \"Road's closed, foreigner.\"", 30);
    sleep_ms(700); cout << endl;
    typeWriter("  He grins. Three teeth missing.", 30);
    sleep_ms(700); cout << endl;
    typeWriter("  \"Turn around and I'll only take one hand.\"", 30);
    sleep_ms(900); cout << endl;
    cout << endl;

    // === CHOICE 3: THE GATE ===
    printLine("~", 60);
    typeWriter("  He has two companions behind him.", 30);
    cout << endl;
    typeWriter("  They are not paying attention.", 30);
    cout << endl;
    cout << endl;
    typeWriter("  How do you proceed?", 30);
    cout << endl;
    printLine("~", 60);
    cout << endl;
    cout << "  [1] Draw your blade immediately." << endl;
    cout << "      Fast. Loud. Brutal." << endl;
    cout << "      (+20 Gold, -8 HP)" << endl;
    cout << endl;
    cout << "  [2] Pretend to comply, get close, then strike." << endl;
    cout << "      Deception before steel." << endl;
    cout << "      (+1 min dmg, +1 max dmg)" << endl;
    cout << endl;
    cout << "  [3] Walk past him without a word." << endl;
    cout << "      Force him to make the first move." << endl;
    cout << "      (+2 permanent Defense)" << endl;
    cout << endl;
    cout << "  Choice: ";

    int c3; cin >> c3;
    cout << endl;

    if (c3 == 1) {
        typeWriter("  Your blade is out before he finishes his sentence.", 30);
        sleep_ms(700); cout << endl;
        typeWriter("  The other two reach for their weapons.", 30);
        sleep_ms(600); cout << endl;
        typeWriter("  They are too slow.", 30);
        sleep_ms(700); cout << endl;
        cout << endl;
        screenFlash("STEEL MEETS FLESH. THE GATE FALLS SILENT.");
        typeWriter("  Seventeen seconds. Three men.", 30);
        sleep_ms(600); cout << endl;
        typeWriter("  You count the coins in their pockets.", 30);
        sleep_ms(800); cout << endl;
        p.gold += 20;
        p.hp = max(1, p.hp - 8);
        slowPrint("\n  >> +20 Gold | -8 HP (Speed has a cost. So does mercy.)");

    } else if (c3 == 2) {
        typeWriter("  You bow your head.", 30);
        sleep_ms(600); cout << endl;
        typeWriter("  \"Of course. Forgive me.\"", 30);
        sleep_ms(600); cout << endl;
        typeWriter("  You step forward as if to turn.", 30);
        sleep_ms(700); cout << endl;
        cout << endl;
        typeWriter("  The guard relaxes.", 30);
        sleep_ms(700); cout << endl;
        cout << endl;
        screenFlash("THAT IS WHEN YOU MOVE.");
        typeWriter("  He never sees it. Neither do the other two.", 30);
        sleep_ms(700); cout << endl;
        typeWriter("  Deception is not dishonor.", 30);
        sleep_ms(700); cout << endl;
        typeWriter("  Not when the enemy deserves neither warning nor mercy.", 30);
        sleep_ms(1000); cout << endl;
        p.weapon.minDmg += 1;
        p.weapon.maxDmg += 1;
        slowPrint("\n  >> Weapon Damage +1/+1 (Patience is the sharpest edge.)");

    } else {
        typeWriter("  You walk forward.", 30);
        sleep_ms(600); cout << endl;
        typeWriter("  The guard blinks.", 30);
        sleep_ms(600); cout << endl;
        typeWriter("  \"Hey -- I said road's closed!\"", 30);
        sleep_ms(700); cout << endl;
        cout << endl;
        typeWriter("  He reaches for you.", 30);
        sleep_ms(700); cout << endl;
        typeWriter("  That reach is his last decision.", 30);
        sleep_ms(800); cout << endl;
        cout << endl;
        screenFlash("YOU ONLY DRAW WHEN THEY TOUCH YOU FIRST.");
        typeWriter("  The fight is brief and entirely one-sided.", 30);
        sleep_ms(700); cout << endl;
        typeWriter("  You are unmarked. They are not.", 30);
        sleep_ms(1000); cout << endl;
        p.defense += 2;
        slowPrint("\n  >> Defense +2 (Composure is a weapon few warriors carry.)");
    }

    sleep_ms(1000);
    cout << endl;

    // === SCENE 5: THE OATH ===
    cout << endl;
    printLine("-", 60);
    typeWriter("  SCENE V  --  THE OATH", 30);
    cout << endl;
    printLine("-", 60);
    sleep_ms(500); cout << endl;

    typeWriter("  You stand over the fallen men.", 30);
    sleep_ms(700); cout << endl;
    typeWriter("  The road north stretches into darkness.", 30);
    sleep_ms(700); cout << endl;
    cout << endl;
    typeWriter("  Somewhere at the end of it:", 30);
    sleep_ms(600); cout << endl;
    typeWriter("  Jinpachi. Raijin. Muramasa.", 30);
    sleep_ms(700); cout << endl;
    typeWriter("  Katsuro with his silver mask.", 30);
    sleep_ms(700); cout << endl;
    typeWriter("  And behind all of them --", 30);
    sleep_ms(600); cout << endl;
    typeWriter("  Akuma-no-Ken.", 30);
    sleep_ms(1000); cout << endl;
    cout << endl;
    typeWriter("  The Devil Swordsman.", 30);
    sleep_ms(1000); cout << endl;
    cout << endl;

    bloodSplatter();

    typeWriter("  You clean your blade on the grass.", 30);
    sleep_ms(700); cout << endl;
    typeWriter("  You do not pray.", 30);
    sleep_ms(600); cout << endl;
    typeWriter("  You do not hesitate.", 30);
    sleep_ms(700); cout << endl;
    cout << endl;
    typeWriter("  You make one oath, quietly, to no one:", 30);
    sleep_ms(700); cout << endl;
    cout << endl;

    sleep_ms(400);
    printLine("*", 60);
    typeWriter("  \"Every man who wore that black crest", 40);
    cout << endl;
    typeWriter("   will answer for what they did.\"", 40);
    cout << endl;
    typeWriter("  \"Every. Single. One.\"", 40);
    cout << endl;
    printLine("*", 60);
    sleep_ms(1200);

    showSwordArt();

    typeWriter("  You walk north.", 30);
    sleep_ms(600); cout << endl;
    cout << endl;

    // === ORIGIN SUMMARY ===
    printLine("=", 60);
    slowPrint("  YOUR ORIGIN IS SET. THE OATH IS MADE.");
    printLine("=", 60);
    cout << endl;
    cout << "  Name      : " << p.name << endl;
    cout << "  HP        : " << p.hp << "/" << p.maxHp << endl;
    cout << "  Stamina   : " << p.stamina << "/" << p.maxStamina << endl;
    cout << "  Defense   : " << p.defense << endl;
    cout << "  Gold      : " << p.gold << endl;
    cout << "  Weapon    : " << p.weapon.name
         << " [" << p.weapon.minDmg << "-" << p.weapon.maxDmg << "]" << endl;
    cout << "  Inventory : ";
    if (p.inventory.empty()) cout << "Empty";
    for (auto& item : p.inventory) cout << item << " ";
    cout << endl;
    printLine("=", 60);
    cout << endl;
    slowPrint("  The road is long. The blade is sharp.");
    slowPrint("  Japan will remember your name.");
    cout << endl;
    cout << "  Press ENTER to begin Level 1..." << endl;
    cin.ignore(); cin.get();
}

// ============================================================
//  MAIN
// ============================================================
int main() {
    srand((unsigned)time(0));

    cout << "\n\n\n\n";
    printLine("=", 60);
    cout << endl;
    sleep_ms(400);
    typeWriter("  . . . . . . . . . . . . . . . . . . . . . . . . . . .", 18);
    cout << endl;
    sleep_ms(300);
    cout << endl;
    typeWriter("        This game contains dark themes.", 35);
    cout << endl;
    typeWriter("        Violence. Loss. Ruthless choices.", 35);
    cout << endl;
    typeWriter("        Play with the lights on.", 35);
    cout << endl;
    cout << endl;
    typeWriter("  . . . . . . . . . . . . . . . . . . . . . . . . . . .", 18);
    cout << endl;
    cout << endl;
    printLine("=", 60);
    sleep_ms(600);
    cout << endl;
    cout << "  Press ENTER to enter feudal Japan..." << endl;
    cin.ignore(); cin.get();

    Player pradeep;

    playOpeningStory(pradeep);

    for (int lvl = 1; lvl <= 5; lvl++) {
        bool survived = playLevel(pradeep, lvl);
        if (!survived) {
            printLine("!", 60);
            slowPrint("  The road ends here.");
            sleep_ms(500);
            slowPrint("  Pradeep falls.");
            sleep_ms(500);
            slowPrint("  Japan weeps in silence.");
            sleep_ms(800);
            printLine("!", 60);
            cout << endl;
            cout << "  [1] Renew the oath -- restart" << endl;
            cout << "  [2] Sheathe the blade -- quit" << endl;
            cout << "  Choice: ";
            int r; cin >> r;
            if (r == 1) {
                pradeep = Player();
                cout << endl;
                slowPrint("  The oath is renewed. The road begins again.");
                sleep_ms(800);
                playOpeningStory(pradeep);
                lvl = 0;
                continue;
            } else {
                slowPrint("  The blade rests. For now.");
                break;
            }
        }
    }

    showEnding(pradeep);
    return 0;
}