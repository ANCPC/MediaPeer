import os

ROOT = "MediaPeer"

folders = [
    "",
    "server",
    "server/api",
    "server/auth",
    "server/database",
    "server/search",
    "server/torrent",
    "server/analytics",
    "server/moderation",
    "server/notification",
    "server/include",
    "server/models",
    "server/utils",

    "website",
    "website/pages",
    "website/pages/home",
    "website/pages/watch",
    "website/pages/creator",
    "website/pages/login",
    "website/pages/upload",
    "website/pages/settings",
    "website/pages/admin",

    "website/css",
    "website/js",

    "website/assets",
    "website/assets/icons",
    "website/assets/fonts",
    "website/assets/images",

    "website/components",
    "website/components/header",
    "website/components/sidebar",
    "website/components/video_card",
    "website/components/comment",
    "website/components/creator_card",

    "storage",
    "storage/database",
    "storage/thumbnails",
    "storage/avatars",
    "storage/banners",
    "storage/cache",
    "storage/temp",
    "storage/exports",

    "config",
    "logs",
    "docs",
    "tests",
    "scripts",
    "build",

    "third_party",
    "third_party/sqlite",
    "third_party/libtorrent",
    "third_party/drogon",
    "third_party/json",
    "third_party/spdlog",
]

files = [

    # Root
    "README.md",
    "CMakeLists.txt",

    # Server
    "server/main.cpp",
    "server/server.cpp",
    "server/server.h",

    # API
    "server/api/login.cpp",
    "server/api/login.h",
    "server/api/logout.cpp",
    "server/api/logout.h",
    "server/api/register.cpp",
    "server/api/register.h",
    "server/api/search.cpp",
    "server/api/search.h",
    "server/api/video.cpp",
    "server/api/video.h",
    "server/api/creator.cpp",
    "server/api/creator.h",
    "server/api/comment.cpp",
    "server/api/comment.h",
    "server/api/subscription.cpp",
    "server/api/subscription.h",
    "server/api/analytics.cpp",
    "server/api/analytics.h",
    "server/api/admin.cpp",
    "server/api/admin.h",

    # Auth
    "server/auth/login.cpp",
    "server/auth/login.h",
    "server/auth/password.cpp",
    "server/auth/password.h",
    "server/auth/session.cpp",
    "server/auth/session.h",
    "server/auth/token.cpp",
    "server/auth/token.h",
    "server/auth/permissions.cpp",
    "server/auth/permissions.h",

    # Database
    "server/database/database.cpp",
    "server/database/database.h",
    "server/database/users.cpp",
    "server/database/users.h",
    "server/database/videos.cpp",
    "server/database/videos.h",
    "server/database/comments.cpp",
    "server/database/comments.h",
    "server/database/likes.cpp",
    "server/database/likes.h",
    "server/database/subscriptions.cpp",
    "server/database/subscriptions.h",
    "server/database/playlists.cpp",
    "server/database/playlists.h",

    # Search
    "server/search/search.cpp",
    "server/search/search.h",
    "server/search/ranking.cpp",
    "server/search/ranking.h",
    "server/search/autocomplete.cpp",
    "server/search/autocomplete.h",
    "server/search/tags.cpp",
    "server/search/tags.h",

    # Torrent
    "server/torrent/peer.cpp",
    "server/torrent/peer.h",
    "server/torrent/magnet.cpp",
    "server/torrent/magnet.h",
    "server/torrent/stream.cpp",
    "server/torrent/stream.h",
    "server/torrent/piece.cpp",
    "server/torrent/piece.h",
    "server/torrent/tracker.cpp",
    "server/torrent/tracker.h",

    # Analytics
    "server/analytics/views.cpp",
    "server/analytics/views.h",
    "server/analytics/watchtime.cpp",
    "server/analytics/watchtime.h",
    "server/analytics/creatorstats.cpp",
    "server/analytics/creatorstats.h",
    "server/analytics/revenue.cpp",
    "server/analytics/revenue.h",

    # Moderation
    "server/moderation/reports.cpp",
    "server/moderation/reports.h",
    "server/moderation/bans.cpp",
    "server/moderation/bans.h",
    "server/moderation/flags.cpp",
    "server/moderation/flags.h",
    "server/moderation/copyright.cpp",
    "server/moderation/copyright.h",

    # Notification
    "server/notification/subscribe.cpp",
    "server/notification/subscribe.h",
    "server/notification/push.cpp",
    "server/notification/push.h",
    "server/notification/email.cpp",
    "server/notification/email.h",

    # Website
    "website/pages/home/index.html",
    "website/pages/watch/watch.html",
    "website/pages/creator/creator.html",
    "website/pages/login/login.html",
    "website/pages/upload/upload.html",
    "website/pages/settings/settings.html",
    "website/pages/admin/admin.html",

    "website/css/main.css",
    "website/css/watch.css",
    "website/css/creator.css",
    "website/css/login.css",
    "website/css/mobile.css",

    "website/js/api.js",
    "website/js/watch.js",
    "website/js/search.js",
    "website/js/comments.js",
    "website/js/login.js",
    "website/js/upload.js",
    "website/js/creator.js",

    # Config
    "config/server.json",
    "config/database.json",
    "config/torrent.json",
    "config/security.json",

    # Docs
    "docs/API.md",
    "docs/Database.md",
    "docs/Protocol.md",
    "docs/DeveloperGuide.md",

    # Logs
    "logs/server.log",
    "logs/error.log",
    "logs/access.log",

    # Database placeholder
    "storage/database/mediapeer.db",
]


print("Creating folders...")

for folder in folders:
    os.makedirs(os.path.join(ROOT, folder), exist_ok=True)

print("Creating files...")

for file in files:
    path = os.path.join(ROOT, file)

    os.makedirs(os.path.dirname(path), exist_ok=True)

    if not os.path.exists(path):
        with open(path, "w", encoding="utf-8") as f:

            if path.endswith(".cpp"):
                name = os.path.basename(path).replace(".cpp", ".h")
                f.write(f'#include "{name}"\n')

            elif path.endswith(".h"):
                guard = (
                    os.path.basename(path)
                    .replace(".", "_")
                    .upper()
                )
                f.write("#pragma once\n")

            elif path.endswith(".json"):
                f.write("{}")

            elif path.endswith(".html"):
                f.write("<!DOCTYPE html>\n<html>\n<head></head>\n<body>\n</body>\n</html>")

            elif path.endswith(".css"):
                f.write("")

            elif path.endswith(".js"):
                f.write("")

            elif path.endswith(".md"):
                f.write("# " + os.path.basename(path).replace(".md", ""))

            else:
                f.write("")

print("\nDone!")
print(f"Project created in: {os.path.abspath(ROOT)}")