import time
import random
import sys

# ============================================================
# UTILITY
# ============================================================
def sleep_ms(ms):
    time.sleep(ms / 1000)

def print_line(ch="-", length=60):
    print(ch * length)

def slow_print(text, delay=25):
    for c in text:
        print(c, end='', flush=True)
        sleep_ms(delay)
    print()

def safe_input(minv=1, maxv=5):
    while True:
        try:
            x = int(input("  Choice: "))
            if minv <= x <= maxv:
                return x
            print(f"  Enter number between {minv} and {maxv}")
        except:
            print("  Invalid input! Please try again.")

def play_sound(effect="slash"):
    try:
        if effect == "slash":
            print('\a', end='', flush=True)
        elif effect == "heavy":
            for _ in range(3): print('\a', end='', flush=True); sleep_ms(70)
        elif effect == "blood":
            for _ in range(6): print('\a', end='', flush=True); sleep_ms(40)
        elif effect == "victory":
            print('\a', end='', flush=True); sleep_ms(150)
            print('\a', end='', flush=True); sleep_ms(100)
            print('\a', end='', flush=True)
    except:
        pass

# ============================================================
# VISUAL EFFECTS
# ============================================================
def health_bar(current, maximum, length=25):
    filled = int(length * current / maximum)
    bar = "█" * filled + "░" * (length - filled)
    return f"[{bar}] {current}/{maximum}"

def particle_slash():
    play_sound("slash")
    print("\n    ⚔️  SLASH ⚔️")
    for _ in range(3):
        print("   /|   *   |\\")
        sleep_ms(60)
    print("  POWERFUL STRIKE!")

def blood_explosion():
    play_sound("blood")
    print("\n    💥 BLOOD EXPLOSION 💥")
    for _ in range(4):
        print("   *   *   *   *")
        sleep_ms(50)

def cherry_blossom():
    play_sound("victory")
    print("\n   🌸  CHERRY BLOSSOMS  🌸")
    for _ in range(4):
        print("     🌸     🌸     🌸")
        sleep_ms(70)

# ============================================================
# PLAYER
# ============================================================
class Player:
    def __init__(self):
        self.hp = self.max_hp = 120
        self.stamina = self.max_stamina = 100
        self.gold = 80
        self.level = 1
        self.xp = 0
        self.xp_next = 100
        self.defense = 6
        self.weapon = {"name": "Wooden Bokken", "min": 6, "max": 14}
        self.inventory = ["Herb Tea", "Herb Tea"]
        self.honor = 50

def check_level_up(p):
    while p.xp >= p.xp_next:
        p.xp -= p.xp_next
        p.level += 1
        p.xp_next = p.level * 100
        p.max_hp += 25
        p.hp = p.max_hp
        p.max_stamina += 15
        p.stamina = p.max_stamina
        p.defense += 3
        cherry_blossom()
        slow_print(f"  ✨ LEVEL UP! YOU ARE NOW LEVEL {p.level} ✨")

# ============================================================
# BOSSES WITH RICH DIALOGUE
# ============================================================
def get_boss(level):
    bosses = {
        1: {"name": "Jinpachi the Scarred", "hp": 110, "min_dmg": 12, "max_dmg": 22, "defense": 7,
            "intro": "You dare challenge me, foreigner? My scars are deeper than your blade!",
            "death": "You fight well... Remember my name..."},
        2: {"name": "Raijin the Thunder Fist", "hp": 145, "min_dmg": 15, "max_dmg": 27, "defense": 9,
            "intro": "I am the storm that breaks empires!",
            "death": "Even thunder... must fall..."},
        3: {"name": "Muramasa the Mad Priest", "hp": 175, "min_dmg": 17, "max_dmg": 30, "defense": 10,
            "intro": "Blood shall rebirth this cursed land!",
            "death": "The gods have abandoned me..."},
        4: {"name": "Katsuro the Shadow Shogun", "hp": 220, "min_dmg": 20, "max_dmg": 34, "defense": 13,
            "intro": "A man without clan dares face me?",
            "death": "A worthy rival..."},
        5: {"name": "Akuma-no-Ken", "hp": 310, "min_dmg": 25, "max_dmg": 42, "defense": 17,
            "intro": "Come, Pradeep... Show me the strength of your soul!",
            "death": "You are the greatest warrior I have faced..."}
    }
    return bosses.get(level, bosses[5])

# ============================================================
# COMBAT
# ============================================================
def fight(p, enemy, is_boss=False, level=1):
    e_hp = enemy["hp"]
    e_max = enemy["hp"]
    
    print_line("#")
    if is_boss:
        slow_print(f"  ⚔️ BOSS BATTLE: {enemy['name']} ⚔️")
        slow_print(f"  {enemy['intro']}")
    else:
        slow_print(f"  {enemy['name']} blocks your path!")
    print_line("#")

    while e_hp > 0 and p.hp > 0:
        print("\n" + "="*65)
        print(f"  ENEMY: {enemy['name']}")
        print(f"  {health_bar(e_hp, e_max)}")
        print(f"  YOU: Pradeep  {health_bar(p.hp, p.max_hp)}")
        print(f"  Stamina: {health_bar(p.stamina, p.max_stamina, 18)}")
        print("="*65)

        print("\n  [1] Strike  [2] Heavy Strike (20)  [3] Parry (15)")
        print("  [4] Herb Tea  [5] Inventory")
        ch = safe_input(1,5)

        dmg = 0
        if ch == 1:
            dmg = random.randint(p.weapon["min"], p.weapon["max"])
            particle_slash()
        elif ch == 2:
            if p.stamina >= 20:
                p.stamina -= 20
                dmg = random.randint(p.weapon["min"]*2, p.weapon["max"]*2)
                slow_print("  💥 HEAVY STRIKE FROM THE HEART!")
                play_sound("heavy")
            else:
                slow_print("  Not enough stamina!")
        elif ch == 3:
            if p.stamina >= 15:
                p.stamina -= 15
                if random.randint(1,100) > 35:
                    slow_print("  PERFECT PARRY & COUNTER!")
                    particle_slash()
                    dmg = random.randint(p.weapon["min"], p.weapon["max"]) + 15
                else:
                    slow_print("  Parry failed...")
            else:
                slow_print("  Not enough stamina!")
        elif ch == 4 and p.inventory:
            p.inventory.pop(0)
            heal = random.randint(25,40)
            p.hp = min(p.max_hp, p.hp + heal)
            slow_print(f"  🌿 +{heal} HP restored!")
        elif ch == 5:
            print("  Inventory:", p.inventory if p.inventory else "Empty")
            continue

        e_hp -= max(0, dmg - enemy["defense"])
        if dmg > 0:
            slow_print(f"  You dealt {max(0, dmg - enemy['defense'])} damage!")

        if e_hp <= 0:
            blood_explosion()
            break

        # Enemy Attack
        edmg = random.randint(enemy["min_dmg"], enemy["max_dmg"])
        actual = max(0, edmg - p.defense)
        if random.randint(1,100) > 65:
            actual = int(actual * 1.6)
            slow_print(f"  {enemy['name']} unleashes a FIERCE attack!")
        else:
            slow_print(f"  {enemy['name']} attacks!")
        
        p.hp -= actual
        slow_print(f"  You took {actual} damage!")
        p.stamina = min(p.max_stamina, p.stamina + 12)

    if p.hp <= 0:
        slow_print("  💀 Your blade falls silent... The legend ends.")
        return False

    slow_print(f"  {enemy.get('death', 'The enemy is slain!')}")
    p.xp += enemy.get("xp", 60)
    p.gold += enemy.get("gold", 80)
    check_level_up(p)
    return True

# ============================================================
# MAIN GAME
# ============================================================
def main():
    random.seed()
    p = Player()

    print_line("=", 75)
    slow_print("          K A T A N A   N O   P R A D E E P", 35)
    print_line("=", 75)
    slow_print("       A Tale of Vengeance, Honor & Steel", 40)

    input("\n  Press ENTER to begin your legend...")

    # Opening Story
    slow_print("\n  Your caravan was burned by the Orochi Clan...")
    blood_explosion()
    slow_print("  A dying boy gave you the serpent crest...")
    
    print("  [1] Save the boy (+Max HP)")
    print("  [2] Move with ruthless speed (+Gold)")
    print("  [3] Listen to his full story (+Defense)")
    c = safe_input(1,3)
    if c == 1: p.max_hp += 35; p.hp = p.max_hp
    elif c == 2: p.gold += 150; p.max_stamina += 35
    else: p.defense += 8

    slow_print("\n  You make the sacred oath:")
    slow_print("  \"Every man who wore the black crest shall fall by my blade!\"")

    # Main Game Loop
    for level in range(1, 6):
        slow_print(f"\n  🔥 LEVEL {level} - PATH OF BLOOD 🔥")
        for _ in range(3):
            enemy = {
                "name": "Orochi Warrior",
                "hp": 70 + level*22,
                "min_dmg": 8 + level*2,
                "max_dmg": 16 + level*4,
                "defense": 4 + level,
                "xp": 55,
                "gold": 75,
                "death": "The serpent's servant falls..."
            }
            if not fight(p, enemy, False, level):
                return

        # Boss Fight
        boss = get_boss(level)
        if not fight(p, boss, True, level):
            break

        cherry_blossom()
        slow_print(f"  ✨ LEVEL {level} CLEARED! ✨")

    # Ending
    print_line("=")
    slow_print("          THE LEGEND OF PRADEEP")
    print_line("=")
    cherry_blossom()
    slow_print("  The Orochi Clan has been destroyed.")
    slow_print("  A foreign warrior became one of Japan's greatest samurai.")
    slow_print("  \~ THE END \~")
    print_line("=")

if __name__ == "__main__":
    main()