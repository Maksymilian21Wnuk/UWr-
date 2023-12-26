import json
import aiohttp
import asyncio
import uuid
from priv import API_KEY

# URLs for getting kanye quote and random cat images
KANYE = "https://api.kanye.rest/"
CATS = "https://api.thecatapi.com/v1/images/search?"


async def get_api_cat(session, url_str):
    url_str += API_KEY
    async with session.get(url_str) as response:
        j_file = (await response.json())[0]
        return j_file

async def get_kanye_quote(session):
    async with session.get(KANYE) as response:
        j_file = await response.json()
        return j_file["quote"]

async def download_pic(session, pic_url):
    async with session.get(pic_url) as response:
        img_data = await response.read()
        
        unique_file_name = "cat" + str(uuid.uuid4().hex) + ".jpg"
        
        with open(unique_file_name, 'wb') as handler:
            handler.write(img_data)
    return unique_file_name

async def get_cat_pic(session):
    content = await get_api_cat(session, CATS)
    file_name = await download_pic(session, content["url"])
    return [content["width"], content["height"], file_name]

async def routine():
    items = {"quote" : None, "img_size" : None}
    async with aiohttp.ClientSession() as session:
        items["quote"] = await get_kanye_quote(session)
        items["img_data"] = await get_cat_pic(session)
    return items


