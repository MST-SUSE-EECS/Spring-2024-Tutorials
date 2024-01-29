from typing import List, Optional
from pydantic import BaseModel

#schema for attributes in a blog
class BlogBase(BaseModel):
    title: str
    body: str
    
class Blog(BlogBase):
    class Config():
        from_attributes = True

class User(BaseModel):
    name: str 
    email: str
    password: str
    
class ShowUser(BaseModel):
    name: str 
    email: str
    blogs: List[Blog] = []
    class Config():
        from_attributes = True     
    
#schema for showable items in a blog
class ShowBlog(BaseModel):
    title: str
    body: str
    creator: ShowUser
    
class Login(BaseModel):
    username: str 
    password: str
    
class Token(BaseModel):
    access_token: str 
    token_type: str 
    
class TokenData(BaseModel):
    username: Optional[str] = None