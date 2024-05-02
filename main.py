import flet as ft
from pytube import Playlist
from moviepy.editor import *
import eyed3
from eyed3.id3.frames import ImageFrame
import shutil
import requests
from http.client import IncompleteRead
import os

def main(page: ft.Page):
    page.title = "ytaupldl"
    page.scroll=ft.ScrollMode.ALWAYS

    page.isListing_do_not_disturb = False
    page.isDownloading_do_not_disturb = False

    page.skip_already_downloaded = False

    page.found_author = None
    page.found_title = None
    class VideoInfo:
        thumbnail_url = []
        title = []
        author = []
        status = []
        checkbox = []
    
    video_info = VideoInfo()

    def list_videos_in_playlist(e):
        
        
        if page.isListing_do_not_disturb:
            return
        loading_list_progressbar.visible = True
        video_list_column.controls.clear()
        page.update()
        video_info.thumbnail_url.clear()
        video_info.title.clear()
        video_info.author.clear()
        video_info.status.clear()

        page.isListing_do_not_disturb = True

        yt_playlist = Playlist(link_textbox.value)
        for index, video in enumerate(yt_playlist.videos, start=0):
            try:
                print("%d : %s - %s" %(index, video.author, video.title))

                video_info.thumbnail_url.append(video.thumbnail_url)
                video_info.checkbox.append(ft.Checkbox(value = True))
                
                find_author(video)
                video_list_column.controls.append(ft.Row(controls=[ft.Image(width=64, height=64, src = video_info.thumbnail_url[index]), 
                    ft.TextField(value = video_info.author[index], disabled = True), 
                    ft.TextField(value = video_info.title[index], disabled = True),
                    video_info.checkbox[index]]))
                
            except:
                print("RELISTENING")
                list_videos_in_playlist(e)

        page.isListing_do_not_disturb = False
        loading_list_progressbar.visible = False
        page.update()


    def find_author(video):
        if try_to_find_author.value:
            if  "i.ytimg.com" in video.thumbnail_url and "-" in video.title:
                artist_and_title = video.title.split("-", 1)
                video_info.author.append(artist_and_title[0])
                video_info.title.append(artist_and_title[1]) 
            else: 
                video_info.author.append(video.author)
                video_info.title.append(video.title)
        else:
            video_info.author.append(video.author)
            video_info.title.append(video.title)

    def download_playlist(e):
        if page.isDownloading_do_not_disturb:
            page.isDownloading_do_not_disturb = False
            download_textbutton.text = "Download"
            delete_temps()
            return
        
        page.isDownloading_do_not_disturb = True
        download_textbutton.text = "Stop"

        yt_playlist = Playlist(link_textbox.value)



        try:
            startpoint = int(start_download_point.value)
        except:
            print("Cant convert to int!")
            start_download_point.value = 1
            startpoint = 1

        try:
            endpoint = int(end_download_point.value)
        except:
            print("Cant convert to int!")
            end_download_point.value = len(yt_playlist.videos)
            endpoint = len(yt_playlist.videos)


        if endpoint > len(yt_playlist.videos) or endpoint < 1:
            end_download_point.value = len(yt_playlist.videos)
            endpoint = len(yt_playlist.videos)






        for index, video in enumerate(yt_playlist.videos, start=0):
            if video_info.checkbox[index].value and index >= startpoint and index <= endpoint and not isDownloaded(video) and page.isDownloading_do_not_disturb:
                print("\n%d: ▼ Downloading ❯❯❯ %s - %s ❯❯❯"%(index, video.author, video.title))#    print a message in cli
                page.update()
                try:
                    video.streams.get_lowest_resolution().download(output_path = output_textfield.value, filename="temp.mp4")
                except:
                    print("===ERROR WHILE DOWNLOADING===\nreconnecting...\n\n\n")#    print a message in cli
                    start_point = index
                    download_playlist(start_point)

                video_custom_title = rename(video)
                convert(video_custom_title)
                add_data(video, video_custom_title)


                print("\n🮕🮕🮕 %s 🮕🮕🮕 downloaded!\n\n"%(video_custom_title))

        print("All videos downloaded successfully! 🎉")#    print a message in cli
        
        
        
        
        delete_temps()
        page.isDownloading_do_not_disturb = False
        download_textbutton.text = "Download"
        page.update()

    def delete_temps():
        if os.path.isfile(output_textfield.value + "temp.mp4"):
            os.remove(output_textfield.value + "temp.mp4")
        if os.path.isfile(output_textfield.value + "temp_img.jpg"):
            os.remove(output_textfield.value + "temp_img.jpg")

    def isDownloaded(video):
        video_custom_title = rename(video) + ".mp3"
        if os.path.isfile(output_textfield.value + video_custom_title) and skip_downloaded_videos_switch.value:
            
            print("\n%s - %s was not downloaded because it is already exists" %(video.author, video.title))
            page.update()
            
            return True
        else:
            return False

    def rename(video):
        video_custom_title = None
        if "/" in video.title:
            video_custom_title = video.author + " - " + video.title 
            video_custom_title = video_custom_title.replace('/','-')
        else:
            video_custom_title = video.author + " - " + video.title
            video_custom_title = video_custom_title.replace('/','-')

        return video_custom_title
    

    def convert(video_custom_title):
        video_file = VideoFileClip(os.path.join(output_textfield.value + "temp.mp4"))
        video_file.audio.write_audiofile(os.path.join(output_textfield.value+ video_custom_title +".mp3"))

    
    def skip_already_downloaded_toggle(e):
        page.skip_already_downloaded = skip_downloaded_videos_switch.value
        print(skip_downloaded_videos_switch.value)

    def add_data(video, video_custom_title):
        find_cover(video)
        audiofile = eyed3.load(output_textfield.value + video_custom_title +'.mp3')


        if (audiofile.tag == None):
            audiofile.initTag()


        if try_to_find_author:
            if "i.ytimg.com" in video.thumbnail_url and "-" in video.title: 
                artist_and_title = video.title.split("-", 1)
                print("✍ Author was extracted from the title -> "+ artist_and_title[0])
                page.update()

                audiofile.tag.artist = artist_and_title[0].strip()
                audiofile.tag.title = artist_and_title[1].strip()
            else:
                audiofile.tag.artist = video.author
                audiofile.tag.title = video.title
        else:
            audiofile.tag.artist = video.author
            audiofile.tag.title = video.title


        audiofile.tag.images.set(ImageFrame.FRONT_COVER, open(output_textfield.value + 'temp_img.jpg','rb').read(), 'image/jpeg')

        audiofile.tag.save()



    def find_cover(video):
        url = video.thumbnail_url
        response = requests.get(url, stream=True)
        with open(output_textfield.value+ 'temp_img.jpg', 'wb') as out_file:
            shutil.copyfileobj(response.raw, out_file)
        del response




            
            
    button_style = ft.ButtonStyle(color={
                    ft.MaterialState.HOVERED: ft.colors.GREY_300,
                    ft.MaterialState.FOCUSED: ft.colors.GREY_300,
                    ft.MaterialState.DEFAULT: ft.colors.GREY_400
                })
    
    
        
    link_textbox = ft.TextField(value= "https://www.youtube.com/playlist?list=PL5XXx28x3AqjBQ81ipQOrvaS4ZADAkaYp", border_color=ft.colors.GREY_800,border_radius=0)
    list_all_videos_button = ft.TextButton("Search videos in playlist", on_click = list_videos_in_playlist, style=button_style)

    loading_list_progressbar = ft.ProgressBar(visible = False)
    video_list_column = ft.Column()

    output_textfield = ft.TextField(value="output/", border_color=ft.colors.GREY_800,border_radius=0)
    skip_downloaded_videos_switch = ft.Switch(label="Ignore already downloaded videos",label_position=ft.LabelPosition.LEFT)
    try_to_find_author = ft.Switch(label="Try to find author from the title, not the channel",label_position=ft.LabelPosition.LEFT)
    start_download_point = ft.TextField(label= "start", value=1)
    end_download_point = ft.TextField(label= "end")
    download_textbutton = ft.TextButton("Download", on_click=download_playlist, style=button_style)

    download_column = ft.Column([output_textfield, try_to_find_author, skip_downloaded_videos_switch, ft.Row([start_download_point, end_download_point]) , download_textbutton])
    
    page.add( link_textbox, list_all_videos_button, loading_list_progressbar, download_column, video_list_column,)
    


ft.app(target = main)