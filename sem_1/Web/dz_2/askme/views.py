from django.shortcuts import render

questions_array = [
    {
        "id" : 1,
        "title": "I WIN 100000 DOLLARS IN TAIWAN",
        "answer_count" : 20,
        "answer": "HOW I CAN GET THEM?",
        "tags": ["money", "a lot of money"],
        "likes": 56,
    },
    {
        "id": 2,
        "title": "I WIN 100000 DOLLARS IN TAIWAN AGAIN",
        "answer_count": 10,
        "answer": "HOW I CAN GET THEM? AGAIN",
        "tags": ["money", "a lot of money"],
        "likes": 56,
    },
]

questions_answers_array = [
    {
        "id": 1,
        "text": "i's joke",
        "correct": False,
        "likes": 56,
        "id_question": 1
    },

    {
        "id": 2,
        "text": "I LOVE YOU",
        "correct": True,
        "likes": 32,
        "id_question": 1
    },
]

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

# Create your views here.
def questions (request, *args):
    return render(request, 'askme/questions.html', context={"questions_array": questions_array, "popular_tags": popular_tags, "best_members": best_members, "auth": False})

def hot_questions (request, *args):
    return render(request, 'askme/hot_questions.html', context={"questions_array": questions_array[::-1], "popular_tags": popular_tags, "best_members": best_members, "auth": False})

def questions_with_tag(request, *args, tag_name):
    questions_array_tag = []

    for i in questions_array:
        if tag_name in i["tags"]:
            questions_array_tag.append(i)

    return render(request, 'askme/question_tag.html', context={"questions_array": questions_array_tag, "tag": tag_name, "popular_tags": popular_tags, "best_members": best_members, "auth": False})

def question(request, *args, id):
    for i in questions_array:
        if i["id"] == id:
            question = i

    answers_array = []

    for i in questions_answers_array:
        if i["id_question"] == id:
            answers_array.append(i)

    return render(request, 'askme/question_answers.html', context={"question": question, "answers_array": answers_array, "popular_tags": popular_tags, "best_members": best_members, "auth": False})

def ask(request, *args):
    return render(request, 'askme/ask.html', context={"popular_tags": popular_tags, "best_members": best_members, "auth": True})