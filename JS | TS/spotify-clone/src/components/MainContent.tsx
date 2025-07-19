import { Button } from "@/components/ui/button";
import { Input } from "@/components/ui/input";
import { Search } from "lucide-react";
import AlbumCard from "./AlbumCard";

const MainContent = () => {
  const recentlyPlayed = [
    { title: "Today's Top Hits", artist: "Spotify", type: "Playlist" },
    { title: "Discover Weekly", artist: "Spotify", type: "Playlist" },
    { title: "Release Radar", artist: "Spotify", type: "Playlist" },
    { title: "Liked Songs", artist: "Spotify", type: "Playlist" },
    { title: "Daily Mix 1", artist: "Spotify", type: "Playlist" },
    { title: "Chill Hits", artist: "Spotify", type: "Playlist" },
  ];

  const madeForYou = [
    { title: "Daily Mix 1", artist: "Various Artists", type: "Made for you" },
    { title: "Daily Mix 2", artist: "Various Artists", type: "Made for you" },
    { title: "Daily Mix 3", artist: "Various Artists", type: "Made for you" },
    { title: "Discover Weekly", artist: "Various Artists", type: "Made for you" },
    { title: "Release Radar", artist: "Various Artists", type: "Made for you" },
  ];

  const popularAlbums = [
    { title: "After Hours", artist: "The Weeknd", type: "Album" },
    { title: "Future Nostalgia", artist: "Dua Lipa", type: "Album" },
    { title: "Positions", artist: "Ariana Grande", type: "Album" },
    { title: "Folklore", artist: "Taylor Swift", type: "Album" },
    { title: "Hollywood's Bleeding", artist: "Post Malone", type: "Album" },
  ];

  return (
    <div className="flex-1 bg-background overflow-auto">
      <header className="sticky top-0 bg-background/95 backdrop-blur-sm border-b border-border p-4">
        <div className="flex items-center gap-4">
          <div className="relative flex-1 max-w-md">
            <Search className="absolute left-3 top-1/2 transform -translate-y-1/2 text-muted-foreground w-4 h-4" />
            <Input
              placeholder="What do you want to listen to?"
              className="pl-10 bg-card border-border"
            />
          </div>
          <Button variant="outline" size="sm">
            Log in
          </Button>
          <Button size="sm" className="bg-primary hover:bg-primary/90">
            Sign up
          </Button>
        </div>
      </header>

      <main className="p-6">
        <section className="mb-8">
          <h2 className="text-2xl font-bold text-foreground mb-4">Recently played</h2>
          <div className="grid grid-cols-2 md:grid-cols-3 lg:grid-cols-6 gap-4">
            {recentlyPlayed.map((item, index) => (
              <AlbumCard
                key={index}
                title={item.title}
                artist={item.artist}
                type={item.type}
              />
            ))}
          </div>
        </section>

        <section className="mb-8">
          <h2 className="text-2xl font-bold text-foreground mb-4">Made for you</h2>
          <div className="grid grid-cols-2 md:grid-cols-3 lg:grid-cols-5 gap-4">
            {madeForYou.map((item, index) => (
              <AlbumCard
                key={index}
                title={item.title}
                artist={item.artist}
                type={item.type}
              />
            ))}
          </div>
        </section>

        <section className="mb-8">
          <h2 className="text-2xl font-bold text-foreground mb-4">Popular albums</h2>
          <div className="grid grid-cols-2 md:grid-cols-3 lg:grid-cols-5 gap-4">
            {popularAlbums.map((item, index) => (
              <AlbumCard
                key={index}
                title={item.title}
                artist={item.artist}
                type={item.type}
              />
            ))}
          </div>
        </section>
      </main>
    </div>
  );
};

export default MainContent;