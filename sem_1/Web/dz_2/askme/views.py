from django.core.paginator import Paginator
from django.shortcuts import render

questions_array = []
for i in range(1, 100):
    tags = []
    for j in range(1, i):
        tags.append(str(j))

    questions_array.append({
        "title": "I WIN " + str(i) + " DOLLARS IN TAIWAN",
        "id": i,
        "question": "HOW I CAN GET THEM MY " + str(i) + " DOLLARS?",
        "likes": i,
        "answer_count": i,
        "tags": tags
    })

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

def paginate(objects_list, request, per_page=10):
    page = request.GET.get('page')
    p = Paginator(objects_list, per_page)
    page_obj = p.get_page(page)

    return page_obj

# Create your views here.
def questions (request, *args):
    paginated_questions = paginate(questions_array, request)

    return render(request, 'askme/questions.html', context={"questions_array": paginated_questions,
                                                            "url_name": "questions",
                                                            "popular_tags": popular_tags,
                                                            "best_members": best_members,
                                                            "auth": False})

def hot_questions (request, *args):
    paginated_questions = paginate(questions_array[::-1], request)

    return render(request, 'askme/hot_questions.html', context={"questions_array": paginated_questions,
                                                                "url_name": "hot_questions",
                                                                "popular_tags": popular_tags,
                                                                "best_members": best_members,
                                                                "auth": False})

def questions_with_tag(request, *args, tag_name):
    questions_array_tag = []

    for i in questions_array:
        if tag_name in i["tags"]:
            questions_array_tag.append(i)

    paginated_questions = paginate(questions_array_tag, request)

    return render(request, 'askme/question_tag.html', context={"questions_array": paginated_questions,
                                                               "tag": tag_name,
                                                               "url_name": "questions_with_tag",
                                                               "popular_tags": popular_tags,
                                                               "best_members": best_members,
                                                               "auth": False})

def question(request, *args, id):
    for i in questions_array:
        if i["id"] == id:
            question = i

    answers_array = []

    for i in questions_answers_array:
        if i["id_question"] == id:
            answers_array.append(i)

    return render(request, 'askme/question_answers.html', context={"question": question,
                                                                   "answers_array": answers_array,
                                                                   "popular_tags": popular_tags,
                                                                   "best_members": best_members,
                                                                   "auth": False})

def ask(request, *args):
    return render(request, 'askme/ask.html', context={"popular_tags": popular_tags,
                                                      "best_members": best_members,
                                                      "auth": True})