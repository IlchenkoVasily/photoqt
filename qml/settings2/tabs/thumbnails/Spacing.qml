import QtQuick 2.3

import "../../../elements"
import "../../"

EntryContainer {

	id: item_top

	Row {

		spacing: 20

		EntryTitle {

			title: "Spacing Between Thumbnails"
			helptext: "The thumbnails are shown in a row at the lower or upper edge (depending on your setup). They are lined up side by side. Per default, there's no empty space between them, however exactly that can be changed here."

		}

		EntrySetting {

			id: entry

			// This variable is needed to avoid a binding loop of slider<->spinbox
			property int val: 20

			Row {

				spacing: 10

				CustomSlider {

					id: spacing_slider

					width: 500

					minimumValue: 0
					maximumValue: 30

					tickmarksEnabled: true
					stepSize: 1

					onValueChanged:
						entry.val = value

				}

				CustomSpinBox {

					id: spacing_spinbox

					width: 75

					minimumValue: 0
					maximumValue: 30

					suffix: " px"

					value: entry.val

					onValueChanged: {
						if(value%5 == 0)
							spacing_slider.value = value
					}

				}

			}

		}

	}

	function setData() {
		spacing_slider.value = settings.thumbnailSpacingBetween
		entry.val = spacing_slider.value
	}

	function saveData() {
		settings.thumbnailSpacingBetween = spacing_spinbox.value
	}

}