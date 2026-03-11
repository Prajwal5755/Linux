# utility functions for quiz
import json
import os
import requests

PROFILE_FILE = os.path.join(os.path.dirname(__file__), '../profiles.json')
CATEGORY_URL = "https://opentdb.com/api_category.php"

def load_profiles():
    # write u r code here to:
    # - load profiles from profiles.json
        with open(PROFILE_FILE,'r') as f:
            profiles=json.load(f)
            profiles=profiles
            return profiles
        
        
 
    # - return profiles list

def save_profiles(profiles):
    # write u r code here to:
    # - save profiles to profiles.json
    with open(PROFILE_FILE,'w') as f:
        json.dump(profiles,f,indent=4)



def get_profile(username):
    #write u r code here to:
    # - find profile by username
    with open(PROFILE_FILE,'r') as f:
        profiles=json.load(f)
        for profile in profiles:
            if profile['username']==username:
                return profile
    return None
    # - return profile or None



def update_profile(new_profile):
    # write u r code here to:
    # - update or add profile to profiles.json
    profiles=load_profiles()
    for i, profile in enumerate(profiles):
        if profile['username']==new_profile['username']:
            profiles[i]=new_profile
            break
    else:
        profiles.append(new_profile)
    save_profiles(profiles)

def get_categories():
    # write u r code here to:
    # - fetch categories from CATEGORY_URL
    category=requests.request('GET',CATEGORY_URL)
    if category.status_code==200:
        return category.json()
    else:
        return []


    # - handle errors and return categories list
    
