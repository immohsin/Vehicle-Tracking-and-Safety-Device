from django.shortcuts import render
import requests
from django.core.mail import send_mail
from django.conf import settings



from_email = settings.DEFAULT_FROM_EMAIL
message = 'This is my test message'
recipient_list = ['vignesh.keerthy@gmail.com','azimu728@gmail.com','msohel9444@gmail.com','srivatsa.dev@gmail.com']


def home(request):
    if request.method == 'GET':
        return render(request,'vehicle/home.html')
    try:
        data = retrive(request)
        print data
        humid = data['humid']
        heat = data['smoke']
        address = geocode(data['lat'],data['lon'])
        sendmail(address,humid,heat,request)
        return render(request,'vehicle/result.html',{'address':address,'humid':humid,'heat':heat})
    except:
        return render(request,'vehicle/error.html')

def retrive(request):
    firebase_url = "https://vehicle-detection-system.firebaseio.com/"
    res = requests.get(firebase_url + request.POST['reg_no'] + '/' + 'vehicle.json')
    data = res.json()
    return data

def geocode(lat,long):
    try:
        base = "http://maps.googleapis.com/maps/api/geocode/json?"
        params = "latlng={lat},{lon}&sensor={sen}".format(
            lat=lat,
            lon=long,
            sen=True
        )
        url = "{base}{params}".format(base=base, params=params)
        response = requests.get(url)
        data = response.json()
        return data['results'][0]['formatted_address']
    except:
        return "Not able to track"


def sendmail(address,humid,heat,request):
    subject = request.POST['reg_no']
    html_message = 'The adrress of tracked vehicle is: <b>{0}</b><br><br> The humid index is: <b>{1}</b> <br><br> The smoke value is: <b>{2}</b>'.format(address, humid, heat)
    send_mail(subject, message, from_email, recipient_list, fail_silently=False, html_message=html_message)
