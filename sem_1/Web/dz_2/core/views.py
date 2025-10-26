from django.shortcuts import render

# Create your views here.

popular_tags = [
    "perl",
    "python",
    "Education",
    "MySQL",
    "django",
    "Mail.ru",
    "Voloshin",
    "Firefox",
]

best_members = [
    "Mr. Freeman",
    "Dr. House",
    "V. Pipkin",
    "Bender",
    "Queen",
]

def login(request, *args):
    return render(request, 'core/login.html', context={"popular_tags": popular_tags, "best_members": best_members, "auth": False})

def signup(request, *args):
    return render(request, 'core/signup.html', context={"popular_tags": popular_tags, "best_members": best_members, "auth": False})