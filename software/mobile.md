# Mobile

{% tabs %}
{% tab title='javascript' %}

* expo
  * lan: For this to work, on the same wifi network as your computer
    * Fastest, safest. The phone connects to your computer just through your router
  * Tunnel: Under tunnel setting, your computer will setup a tunnel to exp.direct,
    * a domain using the ngrok tunnel service
    * all traffic will go through a proxy in the cloud, but it can punch through most firewalls,
    * will work under more conditions

```sh
# 1. Download
npm install -g expo-cli
expo init my-new-project
cd my-new-project
expo start
npm run eject    # removes the app from the Expo framework
```

{% endtab %}
{% endtabs %}

## Cross Platform

{% tabs %}
{% tab title='javascript' %}

* React native: Crossplatform application

```sh
npm i -g create-react-native-app
create-react-native-app my-project
cd my-project
npm start
yarn add react-native-elements
```

{% endtab %}
{% endtabs %}
