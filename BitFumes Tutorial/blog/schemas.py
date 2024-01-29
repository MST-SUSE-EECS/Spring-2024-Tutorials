from pydantic import BaseModel

#schema for attributes in a blog
class Blog(BaseModel):
    title: str
    body: str 
    
#schema for showable items in a blog
class ShowBlog(BaseModel):
    title: str
    body: str
    class Config():
        from_attributes = True

class User(BaseModel):
    name: str 
    email: str
    password: str
    
class ShowUser(BaseModel):
    name: str 
    email: str
    
    class Config():
        from_attributes = True     