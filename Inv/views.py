from django.shortcuts import render, redirect
from .forms import OrderForm, CustomerForm, ProductForm
from .models import Product, Order, Customer


# Create your views here.


def dashboard(request):
    order = Order.objects.all()
    customer = Customer.objects.all()
    total_order = order.count()
    deliver = order.filter(status='Delivered').count()
    pending = order.filter(status='Pending').count()

    context = {
        'order': order,
        'customer': customer,
        'total_order': total_order,
        'deliver': deliver,
        'pending': pending,
    }
    return render(request, 'Inv/dashboard.html', context)


def product(request):
    item = Product.objects.all()
    context = {
        'item': item
    }
    return render(request, 'Inv/product.html', context)


def customer(request, pk_test):
    customer = Customer.objects.get(id=pk_test)
    order = customer.order_set.all()
    order_count = order.count()

    context = {
        'pk_test': pk_test,
        'order': order,
        'order_count': order_count,
    }
    return render(request, 'Inv/customer.html', context)


def createOrder(request):
    form = OrderForm()
    if request.method == "POST":
        form = OrderForm(request.POST)
        if form.is_valid():
            form.save()
            return redirect('/')
    context = {
        'form': form
    }
    return render(request, 'Inv/order_create.html', context)


def createProduct(request):
    form = ProductForm()
    if request.method == "POST":
        form = ProductForm(request.POST)
        if form.is_valid():
            form.save()
            return redirect('/')
    context = {
        'form': form
    }
    return render(request, 'Inv/product_create.html', context)

def createCustomer(request):
    form = CustomerForm()
    if request.method == "POST":
        form = CustomerForm(request.POST)
        if form.is_valid():
            form.save()
            return redirect('/')
    context = {
        'form': form
    }
    return render(request, 'Inv/customer_create.html', context)


def updateOrder(request, pk):
    order = Order.objects.get(id=pk)
    form = OrderForm(instance=order)
    if request.method == "POST":
        form = OrderForm(request.POST, instance=order )
        if form.is_valid():
            form.save()
            return redirect('/')
    context = {
        'form': form,
    }
    return render(request, 'Inv/order_create.html', context)


def updateProduct(request, pk):
    product = Product.objects.get(id=pk)
    form = ProductForm(instance=product)
    if request.method == "POST":
        form = ProductForm(request.POST, instance=product)
        if form.is_valid():
            form.save()
            return redirect('Product')
    context = {
        'form': form
    }
    return render(request, 'Inv/product_create.html', context)


def deleteOrder(request, pk):
    order = Order.objects.get(id=pk)
    if request.method =="POST":
        order.delete()
        return redirect('/')
    context = {
        'order': order
    }
    return render(request, 'Inv/delete.html', context)


def deleteProduct(request, pk):
    product = Product.objects.get(id=pk)
    if request.method == "POST":
        product.delete()
        return redirect('Product')
    context = {
        'product': product
    }
    return render(request, 'Inv/deleteProduct.html', context)