#!/bin/python3

import datetime
import locale
import time
import os
import re


from bin.packages import *
from bin.colors import *

class AutoTor:
    def __init__(self):
        self.urlIp = 'https://mon-ip.net/geolocalisation_IP/map.php'
        self.patternIp = r"<strong>([^<]+)</strong>:\s*([^<]+)"
        self.InitIp_Info()
        self.proxy_Info = {"host": "127.0.0.1", "port": "9050"}

    def Start(self):
        locale.setlocale(locale.LC_TIME, 'fr_FR.UTF-8')
        os.system("clear")
        print(f'''{Color.BASIC}
                        _          _______
             /\        | |        |__   __|
            /  \  _   _| |_ ___      | | ___  _ __
           / /\ \| | | | __/ _ \     | |/ _ \| '__|
          / ____ \ |_| | || (_) |    | | (_) | |
         /_/    \_\__,_|\__\___/     |_|\___/|_|
                        V 0.2
          from Aiden{Color.RESET}
        ''')

        os.system("sudo systemctl start tor")
        time.sleep(1)

    def Exit(self, status):
        print(f"{Color.RESET}\nAutoTor fermé")
        os.system("sudo systemctl stop tor") if not status else None
        quit()
    
    def InitIp_Info(self):
        self.Ip_info = f"{Color.BASIC}[+] IP changé pour :{Color.RESET}\n"
    
    def GetIpInfo(self):
        self.InitIp_Info()
        proxies = {
            'http': f'socks5://{self.proxy_Info["host"]}:{self.proxy_Info["port"]}',
            'https': f'socks5://{self.proxy_Info["host"]}:{self.proxy_Info["port"]}'
        }

        get_ip = str(requests.get(self.urlIp, proxies=proxies).text)
        
        now = datetime.datetime.now()
        date = now.strftime("%A %d %B %Y à %H:%M:%S")

        matches = re.findall(self.patternIp, get_ip)
        result = {key.strip(): value.strip() for key, value in matches}
        max_length = max(len(key) for key in result.keys())
        for key, items in result.items():
            if key != "Drapeau":
                self.Ip_info += f"\t{Color.BASIC}{key:{max_length}} : {items}{Color.RESET}\n"
        self.Ip_info += f"{Color.BASIC}[ ] Informations récupéré le {date}{Color.RESET}\n"
        return self.Ip_info

    def ReloadIp(self):
        os.system("sudo systemctl reload tor")
        time.sleep(2)
        print(self.GetIpInfo())

    def ChangeFireFoxProxy(self):
        firefox_options = Options()

        firefox_profile = webdriver.FirefoxProfile()
        firefox_profile.set_preference("network.proxy.type", 1)
        firefox_profile.set_preference("network.proxy.socks", self.proxy_Info["host"])
        firefox_profile.set_preference("network.proxy.socks_port", int(self.proxy_Info["port"]))
        firefox_profile.set_preference("network.proxy.socks_version", 5)
        firefox_profile.set_preference("network.proxy.socks_remote_dns", True)
        firefox_profile.update_preferences()

        firefox_options.profile = firefox_profile

        self.driver = webdriver.Firefox(options=firefox_options)

if __name__ == '__main__':
    anonym = AutoTor()
    anonym.Start()
    try:
        print(f"{Color.BASIC}[ ] Changer automatiquement le proxy ? Il ouvrira une page web temporaire avec le proxy. (Y/n) ", end='')
        proxy = input(">> ")
        if proxy.lower() == 'y':
            anonym.ChangeFireFoxProxy()
        elif proxy.lower() == 'n':
            print(f"{Color.WARNING}[!] Penser à changer le proxy par {anonym.proxy_Info['host']}:{anonym.proxy_Info['port']}")
            print(f"\tPour le modifier voir about:preferences#general\n")
        else:
            print(f"{Color.ERROR} [-] Erreur : saisie invalide.")
            anonym.Exit(1)
        
        print(f"{Color.BASIC}[ ] Temps avant prochain changement d'IP (en secondes) ", end='')
        x = input(">> ")
        anonym.Exit(1) if not x.isdigit else None
        print("[ ] Durée de mise en service de ce changement (900 (en secondes) pour qu'il soit en place durant 15 min et 0 pour infini) ", end='')
        lin = input(">> ")
        anonym.Exit(1) if not lin.isdigit else None

        print(anonym.GetIpInfo())
        if int(lin) == int(0):
            while True:
                time.sleep(int(x))
                anonym.ReloadIp()
        else:
            for i in range(int(lin)):
                time.sleep(int(x))
                anonym.ReloadIp()
            anonym.Exit(0)
    except KeyboardInterrupt:
        anonym.Exit(0)
