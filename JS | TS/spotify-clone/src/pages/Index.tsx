import Sidebar from "@/components/Sidebar";
import MainContent from "@/components/MainContent";
import MusicPlayer from "@/components/MusicPlayer";

const Index = () => {
  return (
    <div className="h-screen bg-background flex flex-col">
      <div className="flex flex-1 overflow-hidden">
        <Sidebar />
        <MainContent />
      </div>
      <MusicPlayer />
    </div>
  );
};

export default Index;