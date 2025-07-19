import { Home, Search, Library, Plus, Heart } from "lucide-react";
import { Button } from "@/components/ui/button";

const Sidebar = () => {
  const navItems = [
    { icon: Home, label: "Home", active: true },
    { icon: Search, label: "Search", active: false },
    { icon: Library, label: "Your Library", active: false },
  ];

  const playlists = [
    "Liked Songs",
    "My Playlist #1", 
    "Chill Vibes",
    "Workout Mix",
    "Road Trip",
  ];

  return (
    <div className="w-64 bg-background h-full border-r border-border flex flex-col">
      <div className="p-6">
        <h1 className="text-2xl font-bold text-primary">Spotify</h1>
      </div>

      <nav className="px-3 mb-8">
        {navItems.map((item) => (
          <Button
            key={item.label}
            variant="ghost"
            className={`w-full justify-start mb-2 h-10 ${
              item.active 
                ? "bg-accent text-primary" 
                : "text-muted-foreground hover:text-foreground"
            }`}
          >
            <item.icon className="w-5 h-5 mr-3" />
            {item.label}
          </Button>
        ))}
      </nav>

      <div className="px-3 mb-6">
        <Button variant="ghost" className="w-full justify-start mb-2 h-10 text-muted-foreground hover:text-foreground">
          <Plus className="w-5 h-5 mr-3" />
          Create Playlist
        </Button>
        <Button variant="ghost" className="w-full justify-start h-10 text-muted-foreground hover:text-foreground">
          <Heart className="w-5 h-5 mr-3" />
          Liked Songs
        </Button>
      </div>

      <div className="flex-1 px-3 overflow-y-auto">
        <div className="border-t border-border pt-4">
          {playlists.map((playlist, index) => (
            <Button
              key={index}
              variant="ghost"
              className="w-full justify-start mb-1 h-8 text-sm text-muted-foreground hover:text-foreground"
            >
              {playlist}
            </Button>
          ))}
        </div>
      </div>
    </div>
  );
};

export default Sidebar;