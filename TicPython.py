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
            if self.need_blocked() not in (self.character, self.player):
                number = self.need_blocked()
            else:
                number = self.win_option()
        else:
            number = self.win_option()
        if number == 0:
            number = self.random_move()
        self.change(number, self.character)

    def random_move(self):
        for spot in self.orig:
            if isinstance(spot, int):
                return spot
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
        pos_one_wins = 0
        pos_two_wins = 0
        pos_three_wins = 0
        pos_four_wins = 0
        pos_five_wins = 0
        pos_six_wins = 0
        pos_seven_wins = 0
        pos_eight_wins = 0
        pos_nine_wins = 0

        pos_one = 1
        pos_two = 2
        pos_three = 3
        pos_four = 4
        pos_five = 5
        pos_six = 6
        pos_seven = 7
        pos_eight = 8
        pos_nine = 9

        win_options = self.update_wins()
        for win_option in win_options:
            if self.player in win_option:
                continue
            for win_spot in win_option:
                if win_spot == 1:
                    pos_one_wins += 1
                elif win_spot == 2:
                    pos_two_wins += 1
                elif win_spot == 3:
                    pos_three_wins += 1
                elif win_spot == 4:
                    pos_four_wins += 1
                elif win_spot == 5:
                    pos_five_wins += 1
                elif win_spot == 6:
                    pos_six_wins += 1
                elif win_spot == 7:
                    pos_seven_wins += 1
                elif win_spot == 8:
                    pos_eight_wins += 1
                elif win_spot == 9:
                    pos_nine_wins += 1

        positions = {pos_one:pos_one_wins, pos_two:pos_two_wins, pos_three:pos_three_wins, pos_four:pos_four_wins, pos_five:pos_five_wins, 
                    pos_six:pos_six_wins, pos_seven:pos_seven_wins, pos_eight:pos_eight_wins, pos_nine:pos_nine_wins}
        less_wins = 0
        best_position = 0
        pos = list(positions.keys())
        for position in pos:
            if positions[position] > less_wins: 
                best_position = position
        return best_position

class Game(Board):

    def __init__(self):
        self.player = Player('x')
        self.computer = Computer('o')
        self.player_char = 'x'
        self.computer_char = 'o'
        
    def play(self):
        win = 0
        is_draw = False
        while win == 0 or is_draw == False:
            win = self.win()
            is_draw = self.is_draw()
            self.draw()
            self.player.turn()
            self.computer.make_move()
        if win == 1:
            print("good job you won!")
        elif win == 2:
            print("well... the computer won, better luck next time")
        

    def win(self):
        win_options = self.update_wins()
        for win_option in win_options:
            win_count_player = 0
            win_count_computer = 0
            for win_spot in win_option:
                if win_spot == self.player_char:
                    win_count_player += 1
                    if win_count_player == 3:
                        return 1
                elif win_spot == self.computer_char:
                    win_count_computer += 1
                    if win_count_computer == 3:
                        return 2
        return 0

    def is_draw(self):
        for row in self.orig:
            for spot in row:
                if isinstance(spot, int):
                    return False
        return True


g = Game()
g.play()