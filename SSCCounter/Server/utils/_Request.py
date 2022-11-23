import asyncio
import httpx

async def request(client, url):
    response = await client.get(url)
    return response.text

async def task(url):
    async with httpx.AsyncClient() as client:
        tasks = request(client, url)
        result = await asyncio.gather(tasks)
        return result