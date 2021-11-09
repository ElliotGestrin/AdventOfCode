import elliot_standard_library as es
import copy

file = open("Filer\Dag22.txt")
lines = [(line.strip()) for line in file.readlines()]

class Deck():
    def __init__(self,lines, PlayerId):
        active = False
        self.playerId = PlayerId
        self.deck = []
        self.oldConfigurations = []
        for line in lines:
            if not line and active:
                break
            if line == "Player " + PlayerId + ":":
                active = True
            elif active:
                self.deck.append(int(line))

    def draw(self):
        drawnCard = self.deck.pop(0)
        return drawnCard

    def add_to_deck(self, toAdd):
        self.deck += toAdd

    def isDefeated(self):
        if len(self.deck)==0:
            return True
        else:
            return False

    def score(self):
        sum = 0
        for i in range(1, len(self.deck) + 1):
            print(f"{i} * {self.deck[-i]}")
            sum += i * self.deck[-i]
        return sum

    def canRecur(self, cardDrawn):
        if len(self.deck) >= cardDrawn:
            return True
        else:
            return False

    def copy(self, cardDrawn = None):
        copy = Deck([], self.playerId)
        if cardDrawn == None:
            copy.deck = es.deep_copy_list(self.deck.copy())
        else:
            copy.deck = es.deep_copy_list(self.deck[0:cardDrawn].copy())
        return copy

    def updateOld(self):
        self.oldConfigurations.append(es.deep_copy_list(self.deck))

    def isOld(self):
        if self.deck in self.oldConfigurations[:-1]:
            return True
        else:
            return False
def recursiveCombat(Deck1, Deck2, gameNum):
    round = 1
    oldDecks = []
    #print("------------------------------------------------------------")
    #print(f"GAME {gameNum} STARTS!")
    while not (Deck1.isDefeated() or Deck2.isDefeated()):
        #print(f"\nRound {round} ({gameNum})! \nDeck1: {Deck1.deck} \nDeck2: {Deck2.deck}")
        if (Deck1.deck, Deck2.deck) in oldDecks:
            #print(f"The game ends on round {round} due to staleness! Player 1 wins!")
            #print(f"{oldDecks}")
            winner = Deck1.playerId
            break
        else:
            oldDecks.append((Deck1.deck.copy(),Deck2.deck.copy()))
        card1 = Deck1.draw()
        card2 = Deck2.draw()
        #print(f"{card1} vs {card2}")
        if Deck1.canRecur(card1) and Deck2.canRecur(card2):
            #print(f"Starts a new subgame to find the winner!")
            winner = recursiveCombat(Deck1.copy(card1), Deck2.copy(card2), gameNum + 1)
        elif card1 > card2:
            winner = Deck1.playerId
        elif card2 > card1:
            winner = Deck2.playerId
        #print(f"{winner} wins!")
        if winner == "1":
            Deck1.add_to_deck([card1, card2])
        if winner == "2":
            Deck2.add_to_deck([card2, card1])
        round += 1
        if round == 4000:
            #print(f"The round is 4000!XXXXXXXXXXXXXXXXXXXXXXXXXXXXX")
            #fish()
            pass
    #print("------------------------------------------------------------")
    return winner #The winner of the game ALWAYS won the last round

def main():
    Deck1 = Deck(lines, "1")
    Deck2 = Deck(lines, "2")
    print(f"Deck1: {Deck1.deck}")
    print(f"Deck2: {Deck2.deck}")
    winner = recursiveCombat(Deck1, Deck2, 1)
    if winner == "1":
        winnerDeck = Deck1
    if winner == "2":
        winnerDeck = Deck2
    print(f"The winners is {winner}! {winnerDeck.score()}")



main()
