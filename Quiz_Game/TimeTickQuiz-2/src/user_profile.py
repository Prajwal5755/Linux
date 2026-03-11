# manages user profiles
from utils import get_profile, update_profile

class UserProfile:
    def __init__(self, username):
        # write u r code here to:
        # - load existing profile or create new one
        profile=get_profile(username)
        if profile:
            self.username=profile['username']
            self.score=0
            self.difficulty=profile['difficulty']
            self.high_score=profile['high_score']
            
            
        else:
            self.username=username
            self.score=0
            self.high_score=0
            self.difficulty='easy'
            update_profile({'username':self.username,'score':self.score,'high_score':self.high_score,'difficulty':self.difficulty})
        # - set username, score, high score, difficulty

    def increase_score(self):
        # write u r code here to:
        # - increase score
        if self.score:
            self.score=self.score+10
        else:
            self.score=10
        # - update high score if needed
        if self.score>self.high_score:
            self.high_score=self.score
        # - adapt difficulty based on score
        self.adapt_difficulty()
        # - save profile
        self.save()

    def adapt_difficulty(self):
        # write u r code here to:
        # - adjust difficulty based on score (e.g., hard if score > 50)
        if self.score>50:
            self.difficulty='hard'
        elif self.score>20:
            self.difficulty='medium'
        else:
            self.difficulty='easy'

    def save(self):
        # write u r code here to:
        # - save profile to profiles.json
        update_profile({'username':self.username,'score':self.score,'high_score':self.high_score,'difficulty':self.difficulty})
        
