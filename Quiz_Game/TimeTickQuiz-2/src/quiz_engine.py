 # handles quiz logic and api calls
import requests
import html
import threading
import time
import random
from rich.console import Console

console = Console()
CATEGORY_URL = "https://opentdb.com/api_category.php"
QUESTION_URL = "https://opentdb.com/api.php"

class QuizEngine:
    def __init__(self, profile, num_questions, difficulty, time_limit, category_id):
        self.profile = profile
        self.num_questions = num_questions
        self.difficulty = difficulty
        self.time_limit = time_limit
        self.category_id = category_id
        self.questions = []
        self.score = profile.score

    def fetch_questions(self):
        # write  r code here to:
        # - build params for api call
        params={
            "amount":self.num_questions, 
            "difficulty":self.difficulty, 
            "category":self.category_id
            }
        # - fetch questions from QUESTION_URL
        s=requests.request('GET',QUESTION_URL,params=params)
        # - handle errors and store questions
        if s.status_code==200:
            data=s.json()
            self.questions=data.get('results',[])
        else:
            console.print("[red]Failed to fetch questions[/red]")

    def ask_question(self, question_data):
        # write u r code here to:
        # - decode question and answers
        question_text=html.unescape(question_data['question'])
        options_text=html.unescape(question_data['incorrect_answers'])
        answers_text=html.unescape(question_data['correct_answer'])
        options=options_text + [answers_text]
        random.shuffle(options)
       
        # - show question and options
        console.print(f"[bold][blue]{question_text}[/bold][/blue]")
        for i, opt in enumerate(options):
            console.print(f"{i+1}. {opt}")
        # - use threading to enforce time limit
        def timer():
            time.sleep(self.time_limit)
            console.print(f"\n[red]Time's up! Press anything to continue [/red]")
        t = threading.Thread(target=timer)
        
        t.start()
        # - get user input and check if correct
        user_answer = input("Your answer (number): ")
        if user_answer.isdigit() and 1 <= int(user_answer) <= len(options):
            selected = options[int(user_answer) - 1]
            if selected == answers_text:
                console.print("[green]Correct![/green]")
                return True
            else:
                console.print(f"[red]Wrong! Correct answer: {answers_text}[/red]")
                return False
        else:
            console.print("[red]Invalid option![/red]")
            return False
    

    def run(self):
        # write u r code here to:
        # - fetch questions
        self.fetch_questions()
        # - loop through questions and ask them
        for j in self.questions:
            if self.ask_question(j):
                self.profile.increase_score()
        # - update score and show final results
        final=self.profile.score
        console.print(f"[bold green]Quiz Over! Your score: {final}[/bold green]")
