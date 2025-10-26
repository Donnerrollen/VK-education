from django.urls import path
from . import views

urlpatterns = [
    path('', views.questions, name="questions"),
    path('hot/', views.hot_questions, name="hot_questions"),
    path('tag/<str:tag_name>', views.questions_with_tag, name="questions_with_tag"),
    path('question/<int:id>', views.question, name="question"),
    path('ask', views.ask, name="ask")
]