import subprocess


try:
    check_pip3 = subprocess.check_output('dpkg -s python3-pip', shell=True)
    if str('install ok installed') in str(check_pip3):
        pass
except subprocess.CalledProcessError:
    print('[!] pip3 not installed')
    subprocess.check_output('sudo apt update', shell=True)
    subprocess.check_output('sudo apt install python3-pip -y', shell=True)
    print('[+] pip3 installed succesfully')

try:
    import requests
except Exception:
    print('[!] python3 requests is not installed')
    os.system('pip3 install requests')
    os.system('pip3 install requests[socks]')
    print('[+] python3 requests is installed ')

try:
    from selenium import webdriver
    from selenium.webdriver.firefox.options import Options
except Exception:
    print('[!] python3 selenium is not installed')
    os.system('pip3 install selenium')
    print('[+] python3 selenium is installed ')

try:
    check_tor = subprocess.check_output('which tor', shell=True)
except subprocess.CalledProcessError:
    print('[!] tor is not installed !')
    subprocess.check_output('sudo apt update', shell=True)
    subprocess.check_output('sudo apt install tor -y', shell=True)
    print('[+] tor is installed succesfully ')