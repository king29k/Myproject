from django.urls import path
from .import views

urlpatterns = [
    path('', views.dashboard, name='Home'),
    path('product/', views.product, name='Product'),
    path('customer/<str:pk_test>/', views.customer, name='Customer'),
    path('create_order/', views.createOrder, name='Create_order'),
    path('customer_create/', views.createCustomer, name='Create_customer'),
    path('product_create', views.createProduct, name='Create_product'),
    path('update_order/<str:pk>/', views.updateOrder, name='Update_order'),
    path('update_product/<str:pk>/', views.updateProduct, name='Update_product'),
    path('delete_order/<str:pk>/', views.deleteOrder, name='Delete_order'),
    path('delete_product/<str:pk>/', views.deleteProduct, name='Delete_product'),

]