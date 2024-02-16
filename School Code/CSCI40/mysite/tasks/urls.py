from django.urls import path
from .views import index, recipe_1, recipe_2, recipes_list

urlpatterns = [
    path('', index, name='tasks'),
    path('recipe/1', recipe_1, name="tasks"),
    path('recipe/2', recipe_2, name="tasks"),
    path('recipes/list', recipes_list, name="list")
]

app_name = 'tasks'