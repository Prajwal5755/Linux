# main file to run timetickquiz-2 pro
from user_profile import UserProfile
from quiz_engine import QuizEngine
from rich.console import Console
from utils import get_categories

console = Console()

def main():
    console.print("[bold blue]welcome to timetickquiz pro![/bold blue]")
    # write u r code here to:
    # - prompt for username
    console.print("Enter your username:")
    username = console.input(">> ")
    # - create user profile
    profile=UserProfile(username)

    # - get quiz settings (num questions, difficulty, time limit)
    console.print("Enter number of questions:")
    num_questions = int(console.input(">> "))
    console.print("Enter difficulty (easy, medium, hard):")
    difficulty = console.input(">> ")
    console.print("Enter time limit per question (seconds):")
    time_limit = int(console.input(">> "))
    # - show categories and let user pick one
    categories=get_categories()
    console.print("Select a category:")
    for cat in categories['trivia_categories']:
        console.print(f"{cat['id']}. {cat['name']}")
    category_id = int(console.input(">> "))
    settings=QuizEngine(profile,num_questions,difficulty,time_limit,category_id)
    # - start the quiz
    settings.run()

if __name__ == "__main__":
    main()
    

