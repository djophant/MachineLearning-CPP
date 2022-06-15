import numpy as np 

class LossFunctions:

    def hinge_loss_single(self, feature_vector, label, theta, theta_0):
        y = theta @ feature_vector + theta_0
        return max(0, 1 - y * label)

    def hinge_loss_full(self, feature_matrix, labels, theta, theta_0):
        """
        Finds the total hinge loss on a set of data given specific classification
        parameters.

        Args:
            feature_matrix - A numpy matrix describing the given data. Each row
                represents a single data point.
            labels - A numpy array where the kth element of the array is the
                correct classification of the kth row of the feature matrix.
            theta - A numpy array describing the linear classifier.
            theta_0 - A real valued number representing the offset parameter.


        Returns: A real number representing the hinge loss associated with the
        given dataset and parameters. This number should be the average hinge
        loss across all of the points in the feature matrix.
        """
        ys = feature_matrix @ theta + theta_0
        loss = np.maximum(1 - ys * labels, np.zeros(len(labels)))
        return np.mean(loss)


    