# New York Times Random Headline Generator
This project scrapes the New York Times Facebook page for headline data and then
generates random headlines using a Markov Chain.

### Setup:
A Facebook app id is required to run this project properly.
Edit Page_Scraper/get_fb_posts_fb_page.py to set your Facebook app id and app secret:
```python
app_id = <YOUR_APP_ID>
app_secret = <YOUR_APP_SECRET> # DO NOT SHARE WITH ANYONE!
```

This system can be modified to pull text from other facebook pages as well. Simply
modify the following line within "generate headlines":
```python
PAGE="nytimes"
```

### How to run:
    bash generate_headlines

### Sources:
The Facebook page scraper [get_fb_posts_fb_page.py] was written by github user [minimaxr](https://github.com/minimaxir/facebook-page-post-scraper).
The scraper has been modified to set the scraped facebook page as a command argument.

My Markov-Chain project is used to generate the headlines.

### Example Headlines:
The following headlines were generated on Feb 23rd 2016:
```
OUTPUT:
Why I Call Saul
‘Downton Abbey’ Recap: Mugged by Boko Haram’s Use of Hypergrowth
United Arab Emirates Want to Lose Weight
Donald Trump Is Barred From Major League Baseball
Samantha Bee Prepares for Loaded Nachos
```
