# Audio

> Term

* Bitrate: [ex] stereo 5.1: 512kbps, stereo: 384 kbps, mono: 128kbps
* Codec: Coder + Decoder
  * mp3
    * [+] popular with wide support, space space without noticeable quality loss
    * [-] Limited functionality
  * aac
    * [+] More efficient than MP3, widely supported
    * [-] Limit on audio sounds
  * ac-3
    * [+] surround sound
    * [-] Narrow device support

{% tabs %}
{% tab title='python' %}

```py
from IPython.display import Audio  # create Audio objcet with local mp3 file.
audio = Audio(filename='./test.mp3')
display(audio)
```

{% endtab %}
{% endtabs %}
