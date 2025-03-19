import asyncio
import logging
from aiogram import Bot, Dispatcher, types
from aiogram.types import ParseMode
from aiogram.filters import CommandStart
from aiogram.fsm.state import State, StatesGroup
from aiogram.fsm.context import FSMContext
from aiogram.fsm.storage.memory import MemoryStorage
from aiogram.utils.markdown import hbold

# Укажите ваш токен бота
TOKEN = "YOUR_BOT_TOKEN"
GROUP_CHAT_ID = -1001234567890  # Укажите ID общего чата

# Настройка логирования
logging.basicConfig(level=logging.INFO)

# Создание бота и диспетчера
bot = Bot(token=TOKEN, parse_mode=ParseMode.HTML)
dp = Dispatcher(storage=MemoryStorage())

# Определение состояний
class UserState(StatesGroup):
    waiting_for_nicknames = State()

@dp.message(CommandStart())
async def start(message: types.Message, state: FSMContext):
    await message.answer("Привет! Введи ники пользователей через запятую, которым нужно отправить сообщение.")
    await state.set_state(UserState.waiting_for_nicknames)

@dp.message(UserState.waiting_for_nicknames)
async def set_nicknames(message: types.Message, state: FSMContext):
    nicknames = [nick.strip() for nick in message.text.split(",") if nick.strip()]
    if not nicknames:
        await message.answer("Пожалуйста, введи хотя бы один ник.")
        return
    
    warning_message = "\n".join(
        [f"{hbold(nick)} Дорогой друг! Я вижу, что ты не пользуешься VM и не вышел корректно! "
         "Это мешает другим коллегам работать! Будь так любезен - зайди и выйди правильно!" for nick in nicknames]
    )
    
    await bot.send_message(GROUP_CHAT_ID, warning_message)
    await message.answer("Сообщение отправлено в общий чат.")
    await state.clear()

async def main():
    await dp.start_polling(bot)

if __name__ == "__main__":
    asyncio.run(main())
