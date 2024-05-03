class Plane:
    def __init__(self, plane_coordinates, plane_orientation):
        self.__plane_coordinates = plane_coordinates
        self.__cockpit_coordinates = plane_coordinates[0]
        self.__orientation = plane_orientation

    @property
    def coordinates(self):
        return self.__plane_coordinates

    @property
    def cockpit_coordinates(self):
        return self.__cockpit_coordinates

    @property
    def orientation(self):
        return self.__orientation