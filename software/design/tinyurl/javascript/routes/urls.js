const express = require('express')
const router = express.Router();
const validUrl = require('valid-url')
const shortId = require('shortid')
const config = require('config')

const Url = require('../models/url')

// @route  POST /api/url/shorten
// @desc   Create short URL
router.post('/shorten', (req, res) => {
  const { longUrl } = req.body;
  const baseUrl = config.get('baseurl')
  if (!valid_url.isUri(baseUrl))
    return res.status(401).json('Invalid base url')
  const urlCode = shortid.generate();

  if (validUrl.isUri(longUrl)) {
    try {
      let url = await Url.findOne({ longUrl });
      if (url) {
        res.json(url);
      } else {
        const shortUrl = baseUrl + '/' + urlCode;
        url = new Url({
          longUrl, shortUrl, urlCode, date: new Date()
        })

        await url.save();
        res.json(url);
      }
    }
    catch (err) {
      console.error(err);
      res.status(500).json("Server error")
    }
  }
  else
    res.status(401).json("Invalid url")
})
module.exports = router