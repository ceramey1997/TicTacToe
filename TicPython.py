
class Board():

    orig = [[1,2,3],[4,5,6],[7,8,9]]

    def update_wins(self):
        win1 = [self.orig[0][0], self.orig[0][1], self.orig[0][2]]
        win2 = [self.orig[1][0], self.orig[1][1], self.orig[1][2]]
        win3 = [self.orig[2][0], self.orig[2][1], self.orig[2][2]]
        win4 = [self.orig[0][0], self.orig[1][0], self.orig[2][0]]
        win5 = [self.orig[0][0], self.orig[1][1], self.orig[2][2]]
        win6 = [self.orig[0][1], self.orig[1][1], self.orig[2][1]]
        win7 = [self.orig[0][2], self.orig[1][1], self.orig[2][0]]
        win8 = [self.orig[0][2], self.orig[1][2], self.orig[2][2]]
        win_options = [win1, win2, win3, win4, win5, win6, win7, win8]
        return win_options
    def draw(self):
        for i in range(3):
            for j in range(3):
                if j < 2:
                    print(self.orig[i][j], end="")
                else:
                    print(self.orig[i][j])
    
    def change(self, number, player):
        i, j  = self.get_position(number)        
        self.orig[i][j] = player
        self.update_wins()

    def get_position(self, number_rep):
        if number_rep == 1:
            return 0, 0
        elif number_rep == 2:
            return 0, 1
        elif number_rep == 3:
            return 0, 2
        elif number_rep == 4:
            return 1, 0
        elif number_rep == 5:
            return 1, 1
        elif number_rep == 6:
            return 1, 2
        elif number_rep == 7:
            return 2, 0
        elif number_rep == 8:
            return 2, 1
        elif number_rep == 9:
            return 2, 2

class Player(Board):

    def __init__(self, character):
        self.character = character

    def turn(self):
        number = int(input("what position would you like to play?"))
        self.change(number, self.character)

class Computer(Player):

    def __init__(self, character):
        Player.__init__(self, character)
        if self.character == 'x':
            self.player = 'o'
        else:
            self.player = 'x'

    def make_move(self):
        if self.need_blocked():
            number = self.need_blocked()
        else:
            number = self.win_option()

        self.change(number, self.character)

    def need_blocked(self):
        win_options = self.update_wins()
        for win_option in win_options:
            i = 0
            option = 0

            for win_spot in win_option:
                if win_option[i] == self.player:
                    option += 1
                i += 1        
                if option == 2:                    
                    for win_spot in win_option:   
                        if win_spot != self.player:
                            return win_spot

    def win_option(self):
        win_options = self.update_wins()
        best_option = 0
        best_option_options = 0
        for win_option in win_options:
            win_opertunites = 0
            for win_spot in win_option:
                if win_spot == self.player:
                    break
                if win_spot == self.character:
                    win_opertunities += 2
                else:
                    win_opertunites +=1
                if win_opertunities > best_option_options:
                    best_option_options = win_opertunities
                    best_option = self.get_position(win_spot)

class Game():

    def __init__(self):
        self.board = Board()
        self.player = Player('x')
        self.computer = Computer('o')
        
    def play(self):
        self.player.turn()
        self.player.turn()
        self.computer.make_move()
        self.board.draw()



g = Game()
g.play()
