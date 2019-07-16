class song(object):
    def __init__(self,song):
        self.lyrics = song

    def sing_me_a_song(self):
        for line in self.lyrics:
            print(line)

happy_bday = song(["happy birthday","to you","and mee"])

twinkle_twinkle = song(["twinkle ","twinkle","litte star"])

happy_bday.sing_me_a_song()
twinkle_twinkle.sing_me_a_song()
